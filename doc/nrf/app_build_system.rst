.. _app_build_system:

Build and configuration system
##############################

.. contents::
   :local:
   :depth: 2

The |NCS| build and configuration system is based on the one from Zephyr, with some additions.

Zephyr's build and configuration system
***************************************

Zephyr's build and configuration system uses the following building blocks as a foundation:

* CMake, the cross-platform build system generator
* Kconfig, a powerful configuration system also used in the Linux kernel
* Devicetree, a hardware description language that is used to describe the hardware that the |NCS| is to run on

Since the build and configuration system used by the |NCS| comes from Zephyr, references to the original Zephyr documentation are provided here in order to avoid duplication.
See the following links for information about the different building blocks mentioned above:

* :ref:`zephyr:application` is a complete guide to application development with Zephyr, including the build and configuration system.
* :ref:`zephyr:cmake-details` describes in-depth the usage of CMake for Zephyr-based applications.
* :ref:`zephyr:application-kconfig` contains a guide for Kconfig usage in applications.
* :ref:`zephyr:set-devicetree-overlays` explains how to use devicetree and its overlays to customize an application's devicetree.
* :ref:`board_porting_guide` is a complete guide to porting Zephyr to your own board.

.. _app_build_additions:

|NCS| additions
***************

The |NCS| adds some functionality on top of the Zephyr build and configuration system.
Those additions are automatically included into the Zephyr build system using a :ref:`cmake_build_config_package`.

You must be aware of these additions when you start writing your own applications based on this SDK.

* The Kconfig option :kconfig:option:`CONFIG_WARN_EXPERIMENTAL` is enabled by default.
  It gives warnings at CMake configure time if any experimental feature is enabled.

  For example, when building a sample that enables :kconfig:option:`CONFIG_BT_EXT_ADV`, the following warning is printed at CMake configure time:

  .. code-block:: shell

     warning: Experimental symbol BT_EXT_ADV is enabled.

* The |NCS| provides an additional :file:`boilerplate.cmake` that is automatically included when using the Zephyr CMake package in the :file:`CMakeLists.txt` file of your application::

    find_package(Zephyr HINTS $ENV{ZEPHYR_BASE})

* The |NCS| allows you to :ref:`create custom build type files <gs_modifying_build_types>` instead of using a single :file:`prj.conf` file.
* The |NCS| build system extends Zephyr's with support for multi-image builds.
  You can find out more about these in the :ref:`ug_multi_image` section.
* The |NCS| adds a partition manager, responsible for partitioning the available flash memory.
* The |NCS| build system generates zip files containing binary images and a manifest for use with nRF Cloud FOTA.

.. _app_build_fota:

Building FOTA images
********************

The |NCS| build system places output images in the :file:`<build folder>/zephyr` folder.

If :kconfig:option:`CONFIG_BOOTLOADER_MCUBOOT` is set, the build system creates the :file:`dfu_application.zip` file containing files :file:`app_update.bin` and :file:`manifest.json`.
If you have also set the options :kconfig:option:`CONFIG_IMG_MANAGER` and :kconfig:option:`CONFIG_MCUBOOT_IMG_MANAGER`, the application will be able to process FOTA updates.
If you have set the options :kconfig:option:`CONFIG_SECURE_BOOT` and :kconfig:option:`CONFIG_BUILD_S1_VARIANT`, a similar file :file:`dfu_mcuboot.zip` will also be created.
You can use this file to perform FOTA updates of MCUboot itself.

The :file:`app_update.bin` file is a signed version of your application.
The signature matches to what MCUboot expects and allows this file to be used as an update.
The build system creates a :file:`manifest.json` file using information in the :file:`zephyr.meta` output file.
This includes the Zephyr and |NCS| git hashes for the commits used to build the application.
If your working tree contains uncommitted changes, the build system adds the suffix ``-dirty`` to the relevant version field.

.. _app_build_output_files:

Output build files
******************

The building process produces each time an *image file*.

.. output_build_files_info_start

The image file can refer to an *executable*, a *program*, or an *ELF file*.
As one of the last build steps, the linker processes all object files by locating code, data, and symbols in sections in the final ELF file.
The linker replaces all symbol references to code and data with addresses.
A symbol table is created which maps addresses to symbol names, which is used by debuggers.
When an ELF file is converted into another format, such as HEX or binary, the symbol table is lost.

Depending on the application and the SoC, you can use one or several images.

.. output_build_files_info_end

.. output_build_files_table_start

The following table lists build files that can be generated as output when building firmware for supported :ref:`build targets <app_boards>`.
The table includes files for single-core and multi-core programming scenarios for both |VSC| and command line building methods.
Which files you are going to use depends on the application configuration and not directly on the type of SoC you are using.
The following scenarios are possible:

* Single-image - Only one firmware image file is generated for a single core.
* Multi-image - Two or more firmware image files are generated for a single core.
  You can read more about this scenario in :ref:`ug_multi_image`.
* Multi-core - Two or more firmware image files are generated for two or more cores.

+---------------------------------+-------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------+
| File                            | File format                                                                                     | Programming scenario                                                     |
+=================================+=================================================================================================+==========================================================================+
| :file:`zephyr.hex`              | Default full image.                                                                             | * Programming non-secure domain (``_ns``) or single-image build targets. |
|                                 | In a multi-image build, several :file:`zephyr.hex` are generated, one for each image.           | * Testing DFU procedure with nrfjprog.                                   |
+---------------------------------+-------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------+
| :file:`merged.hex`              | The result of merging all :file:`zephyr.hex` files for all images for a core                    | * Programming multi-core application.                                    |
|                                 | in a multi-image build. Used by Nordic Semiconductor's build targets in single-core             | * Testing DFU procedure with nrfjprog.                                   |
|                                 | multi-image builds. In multi-core builds, several :file:`merged_<domain_name>.hex` fields       |                                                                          |
|                                 | are generated, where *<domain-name>* indicates the core.                                        |                                                                          |
+---------------------------------+-------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------+
| :file:`merged_domain.hex`       | The result of merging all :file:`merged.hex` files for all cores or domains                     | * Programming secure domain (``_s``) and multi-core build targets.       |
|                                 | (:file:`merged.hex` for the application core and :file:`merged.hex` or :file:`zephyr.hex`       | * Testing DFU procedure with nrfjprog.                                   |
|                                 | for the network core).                                                                          |                                                                          |
+---------------------------------+-------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------+
| :file:`app_update.bin`          | Application core update file used to create :file:`dfu_application.zip`.                        | DFU process for single-image build targets and the application core      |
|                                 | Contains the signed version of the application.                                                 | of the multi-core build targets.                                         |
|                                 | This file is transferred in the real-life update procedure, as opposed to HEX files             |                                                                          |
|                                 | that are transferred with nrfjprog when emulating an update procedure.                          |                                                                          |
+---------------------------------+-------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------+
| :file:`net_core_app_update.bin` | Network core update file used to create :file:`dfu_application.zip`.                            | DFU process for the network core of multi-core build targets.            |
|                                 | This file is transferred in the real-life update procedure, as opposed to HEX files             |                                                                          |
|                                 | that are transferred with nrfjprog when emulating an update procedure.                          |                                                                          |
+---------------------------------+-------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------+
| :file:`dfu_application.zip`     | Zip file containing both the MCUboot-compatible update image for one or more cores              | DFU process for both single-core and multi-core applications.            |
|                                 | and a manifest describing its contents.                                                         |                                                                          |
+---------------------------------+-------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------+
| :file:`matter.ota`              | :ref:`ug_matter`-specific OTA image that contains a Matter-compliant header                     | DFU over Matter for both single-core and multi-core applications.        |
|                                 | and a DFU multi-image package that bundles user-selected firmware images.                       |                                                                          |
+---------------------------------+-------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------+
| :file:`<file_name>.zigbee`      | :ref:`ug_zigbee`-specific OTA image that contains the Zigbee application                        | DFU over Zigbee for both single-core and multi-core applications         |
|                                 | with the Zigbee OTA header used for providing information about the image to the OTA server.    | in the |NCS| v2.0.0 and later.                                           |
|                                 | The *<file_name>* includes manufacturer's code, image type, file version, and comment           |                                                                          |
|                                 | (customizable by user, sample name by default).                                                 |                                                                          |
|                                 | For example: :file:`127F-0141-01020003-light_switch.zigbee`.                                    |                                                                          |
+---------------------------------+-------------------------------------------------------------------------------------------------+--------------------------------------------------------------------------+

.. output_build_files_table_end

.. _app_build_output_files_other:

Other output build files
========================

The following table lists secondary build files that can be generated when building firmware, but are only used to create the final output build files listed in the table above.

+---------------------------------+----------------------------------------------------------------------------------------------------------+
| File                            | File format                                                                                              |
+=================================+==========================================================================================================+
| :file:`zephyr.elf`              | An ELF file for the image that is being built. Can be used for debugging purposes.                       |
+---------------------------------+----------------------------------------------------------------------------------------------------------+
| :file:`zephyr.meta`             | A file with the Zephyr and nRF Connect SDK git hashes for the commits used to build the application.     |
+---------------------------------+----------------------------------------------------------------------------------------------------------+
| :file:`manifest.json`           | Output artifact that uses information from the :file:`zephyr.meta` output file.                          |
+---------------------------------+----------------------------------------------------------------------------------------------------------+
| :file:`dfu_multi_image.bin`     | Multi-image package that contains a CBOR manifest and a set of user-selected update images,              |
|                                 | such as firmware images for different cores.                                                             |
|                                 | Used for DFU purposes by :ref:`ug_matter` and :ref:`ug_zigbee` protocols.                                |
+---------------------------------+----------------------------------------------------------------------------------------------------------+
