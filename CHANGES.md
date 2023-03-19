Unreleased
----------
- Major cleanup
- Replace custom Makefile with autotools build system
- Port to GTK 2.0, replace file/option selection widgets
- Improve config file writing and parsing (compatibility break)
- Remove progress "indicator"
- Move several items to a new Palette tab
- Write error output to STDERR instead of a popup dialog
- Reap zombie TuxNES processes
- Update options to conform to latest TuxNES on Github

v0.75 - 2001-04-17
------------------
- Config file now auto-saves on program exit
- Change version number to reflect compatible TuxNES release

v0.3.0 - 2001-03-05 [DEVELOPMENT RELEASE]
-----------------------------------------
- Get rid of TuxNES output redirecting because it was ugly and didn't work right
- Update options to conform to latest TuxNES cvs snap
- Add GTuxNES option saving/loading feature
- Minor cleanup work

v0.2.1 - 2000-08-06 [DEVELOPMENT RELEASE]
-----------------------------------------
- Make combo boxen more user-friendly

v0.2.0 - 2000-07-20 [DEVELOPMENT RELEASE]
-----------------------------------------
- Redirect TuxNES output from STDERR to a popup dialog
- Remove 3 second pause to wait for TuxNES
- Add progress "indicator" while TuxNES launches

v0.74.1 - 2000-07-09
--------------------
- Enable support of `--display=` option

v0.74 - 2000-07-08
------------------
- Fix memory allocation bug
- Change sound sample format choices to match new options
- Change version number to reflect compatible version of TuxNES
- Officially put GTuxNES under the GPL

v0.1.3 - 2000-07-07
-------------------
- Fix renderer choices that I broke in 0.1.2
- Add 'Hz' label to Sound Rate choice
- Fix memory leak created in 0.1.2
- Fix memory leak created when heap overflows
- File selections now 'remember' last used directory
- Clean up code appearance in `gtuxnes.c`

v0.1.2 - 2000-07-06
-------------------
- Add ability to enlarge by non-default amount
- Add ability to specify Joystick device files
- Update renderer choices to match latest devel cvs snap (2000-07-06)
- Update builtin palette choices to match latest devel cvs snap
- Add support for NTSC pallete option

v0.1.1 - 2000-06-20
-------------------
- Minor bug fix related to Scanlines toggle and mirror combo box (thanks Ben)

v0.1 - 2000-06-19
-----------------
- Initial release
