
ADADIO Linux Driver Release Notes

Revision History
================

--------------------------------------------------------------------------------

Version 3.1.9.0 - Released 7/29/2009

- Driver version 3.1.9
- Driver: Fixed detection logic for board's DMDMA support.
- Driver: Modified I/O services to use common argument types.
- Driver: Added dev_check_id() service.
- id: Corrected firmware version number decoding logic.

--------------------------------------------------------------------------------

Version 3.0.5.0 - Released 4/17/2009

- Driver version 3.0.5
- Fixed a DMA bug: the first DMA returned incorrect data
  This was previously and incorrectly reported here as a version 3.0.4.0 mod.
- Modified some PLX register names for consistency.

--------------------------------------------------------------------------------

Version 3.0.4.0 - Released 4/10/2009

- Driver Version: 3.0.4
- This was a complete overhaul of the driver.
- The interface has changed; some services were added and some were removed.

--------------------------------------------------------------------------------

Version 2.0

- Full port to version 2.6 of the kernel.
- Changed interface format to be similar to other Linux drivers.
- Added user manual.

--------------------------------------------------------------------------------
