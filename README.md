<!--
SPDX-FileCopyrightText: 2000-2001 Scott Weber <scott@scottweber.com>
SPDX-License-Identifier: GPL-2.0-or-later
-->

What is GTuxNES?
----------------
GTuxNES is a graphical launcher for the Nintendo emulator TuxNES.  TuxNES
is entirely command line based and I got tired of typing the dozen options
I wanted to use every time I started the emulator.  So my response was to
build GTuxNES.  GTuxNES is built using GTK version 2.0.


Can I use GTuxNES?
------------------
Sure!  All you need is to get and install the GTK 2.0 libraries from your
distribution's package manager.  Then go get the development TuxNES from
<https://github.com/tuxnes/tuxnes>.  Once you've compiled and installed
that, GTuxNES should work for you.  Compile and install GTuxNES using:

    $ autoreconf -if
    $ ./configure
    $ make
    # make install


Where does GTuxNES look for the TuxNES binary?
----------------------------------------------
As long as the TuxNES binary is located in one of the directories in your
`PATH` environment variable and is called `tuxnes` GTuxNES will have no
problem finding it.  If you get any weirdness, putting the `tuxnes` binary
in the same directory as `gtuxnes` should solve your problem.


Where does GTuxNES store the config options?
--------------------------------------------
Right now, it looks for the config file in your home directory (as returned
by `g_get_home_dir()`) and uses the filename `.gtuxnesrc`.  A future release
will hopefully add support for use of multiple config files, specifiable
on the command line.


What happened to the 'Save Config' button?
------------------------------------------
I decided between versions 0.3.0 and 0.75 (which are actually consecutive
versions, despite their wide numerical spread) that it made more sense to
just make GTuxNES auto-save the config file whenever it exited, rather than
forcing the user to manually save whenever a change was made.  So the 'Save
Config' button has kind of merged into the 'Quit' button.  Every time you
exit GTuxNES it will quietly save the current configuration to
`~/.gtuxnesrc`.


What does 'x' option do?
------------------------
A future version of GTuxNES may include a help document that explains
every option available.  For now though, your best bet is to check the
README file in the TuxNES archive.


GTuxNES doesn't work!  You suck!
--------------------------------
Hmm.  That's unfortunate.  Well, if you think you've found a bug, by all
means let me know.  Feel free to fix the bug yourself if you like, then
submit a new Issue or Pull Request at <https://github.com/tuxnes/gtuxnes>.

If you just have something against me, please direct your comments to
your local bit-bucket.


GTuxNES is the coolest thing since sliced bread!
------------------------------------------------
Well I'm not sure it's *that* cool, but thank you!  Feel free to email me
at <scott@scottweber.com>.


How is GTuxNES licensed?
------------------------
This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.


Would you like to plug anything?
--------------------------------
Well, now that you mention it :)

Thanks to the TuxNES guys for a great emulator!
- <https://tuxnes.sourceforge.net/>
- <https://github.com/tuxnes/tuxnes>

Thanks to the GTK guys for a simple, powerful toolkit.
- <https://www.gtk.org/>

Thanks to LUFOG for inspiring me to get Linux working on my computer.
- <http://www.lufog.org/>


-Scott <scott@scottweber.com>
