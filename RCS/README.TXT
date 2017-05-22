head	4.7;
access;
symbols;
locks
	MIKE:4.7;
comment	@# @;


4.7
date	96.04.19.21.12.08;	author MIKE;	state Exp;
branches;
next	3.2;

3.2
date	95.12.12.14.01.01;	author MIKE;	state Exp;
branches;
next	3.1;

3.1
date	95.11.30.18.41.23;	author MIKE;	state Exp;
branches;
next	3.0;

3.0
date	95.11.09.15.57.32;	author MIKE;	state Exp;
branches;
next	2.7;

2.7
date	95.10.26.18.05.29;	author MIKE;	state Exp;
branches;
next	2.6;

2.6
date	95.10.25.12.07.45;	author MIKE;	state Exp;
branches;
next	2.5;

2.5
date	95.10.10.16.57.16;	author MIKE;	state Rel;
branches;
next	2.3;

2.3
date	95.09.24.21.39.04;	author MIKE;	state Rel;
branches;
next	2.2;

2.2
date	95.09.08.13.17.38;	author MIKE;	state Rel;
branches;
next	1.2;

1.2
date	95.08.11.12.12.53;	author MIKE;	state Rel;
branches;
next	1.1;

1.1
date	95.08.10.14.53.45;	author MIKE;	state Rel;
branches;
next	;


desc
@Sentry's Readme file.
@

4.7
log
@*** empty log message ***
@
text
@













                                S e n t r y
                                ===========
                                    V5.0

                             Instruction Manual

                             Copyright (C) 1996

                             Michael A. Bobbitt
                            NightShade Computing
                          Mike.Bobbitt@@AcadiaU.CA
               http://dragon.acadiau.ca/~910318b/Sentry.html




                                S e n t r y
                                ===========
                             Table of Contents

        1.0 Introduction
            1.1  Purpose of Sentry
                 1.1.1 In the Home
                 1.1.2 In a Business Environment
                 1.1.3 In an Educational Environment
                 1.1.4 General
            1.2  Features of Sentry
                 1.2.1 General
                 1.2.2 Expiry Dates
                 1.2.3 Windows
                 1.2.4 File Protection
            1.3  Distribution of Sentry

        2.0 Setup
            2.1  Installing Sentry
            2.2  The Initial Login
            2.3  First Priorities
            2.4  Using the Initialization Settings
            2.5  Uninstalling Sentry

        3.0 Securing Your Computer
            3.1  BIOS Password
            3.2  Boot Sequence
            3.3  SWITCHES in CONFIG.SYS
            3.4  BootKeys in MSDOS.SYS
            3.5  BREAK in CONFIG.SYS
            3.6  Passwords
            3.7  Placement in AUTOEXEC.BAT
            3.8  Keep a Backup

        4.0 Logging In
            4.1  The Login Procedure
            4.2  Changing Passwords

        5.0 The SuperUser Menu
            5.1  The User Maintenance Menu
                 5.1.1  Create User
                 5.1.2  Delete User
                 5.1.3  View Users
                 5.1.4  Toggle SuperUser Status
                 5.1.5  Change Account Exipry Date
                 5.1.6  Change Password Expiry Date
                 5.1.7  Change Account Password
                 5.1.8  Assign Max Invalid Logins
                 5.1.9  Return to SuperUser Menu
            5.2  The Log File Maintenance Menu
                 5.2.1  View Log File
                 5.2.2  View Backup Log File
                 5.2.3  Move Log File to Backup
                 5.2.4  Return to SuperUser Menu
            5.3  Edit Initialization Settings
            5.4  Send a Message to a User
            5.5  Protect a File
            5.6  Export Initialization Settings
            5.7  Sentry DOS Shell
            5.8  Security Audit
            5.9  Exit

        6.0 Using Sentry With Windows
            6.1  General
            6.2  Installation Procedure
            6.3  Windows 95

        7.0 Securing Other Programs
            7.1  General
            7.2  Setup
            7.3  Account Information
            7.4  Using Templates
            7.5  Running a Protected File

        8.0 Creating a new Instance of Sentry

        9.0 Registration
            9.1 General
            9.2 Benefits of Registration

        10.0 The Initialization Settings
             10.1  Location of the Log File
             10.2  Location of the Backup Log File
             10.3  Location of the Message File
             10.4  Minimum Password Length
             10.5  Maximum Password Length
             10.6  Maximum Invalid Tries
             10.7  Wait Time After an Invalid Login
             10.8  Max Log File Size
             10.9  Key to Change Password
             10.10 Password Echo Character
             10.11 Days Until Passwords Expire
             10.12 Days Until Accounts Expire
             10.13 Screen Saver Activation Time
             10.14 Screen Saver Message
             10.15 Login Prompt
             10.16 Password Prompt
             10.17 Wrong Password Message
             10.18 Wrong Login Message
             10.19 Bad Password Length Message
             10.20 Bad Login Length Message
             10.21 Wrong Password Log Message
             10.22 Wrong Login Log Message
             10.23 Bad Password Length Log Message
             10.24 Bad Login Length Log Message
             10.25 Environment Variable
             10.26 Enable Sentry with Windows
             10.27 Show Title
             10.28 Date Format
             10.29 Case Sensitivity
             10.30 Windowed Mode
             10.31 Enable Colour
             10.32 Text Colour
             10.33 Text Background
             10.34 Highlighted Text Colour
             10.35 Highlighted Text Background
             10.36 Maximum Invalid Logins
             10.37 Type Ahead
             10.38 Clear Screen

        11.0 Technical Notes
             11.1  Encoding Algorithm
             11.2  SuperUser Access
             11.3  Files
             11.4  File_id.diz
             11.5  Time / Date
             11.6  Environment Variables
             11.7  Virus Scanners
             11.8  File Deletion
             11.9  General

        12.0 Potential Threats To Security
             12.1  Account Information
             12.2  Hardware Loopholes

        13.0 Troubleshooting
             13.1  Error messages
                   13.1.1  Cannot Locate Environment.
                   13.1.2  Environment Overflow - Not Modified.
                   13.1.3  Error Creating Backup Log File!
                   13.1.4  Error Creating Log File!
                   13.1.5  Error Creating Temp File!
                   13.1.6  Error Opening Log File!
                   13.1.7  Error Opening Message File!
                   13.1.8  Error Opening Protected File!
                   13.1.9  Error Opening Sentry.ins!
                   13.1.10 Error Opening System Files!
                   13.1.11 Error Opening Temp File!
                   13.1.12 Error Reading Data Segment [Open]
                   13.1.13 Please Run the INSTALL.EXE program.
                   13.1.14 Error Scanning Temp File!
                   13.1.15 Error in Account Information!
                   13.1.16 Error in Initialization Settings!
                   13.1.17 Internal Screen Error [Reading]
                   13.1.18 Internal Screen Error [Writing]
                   13.1.19 Out of memory!
                   13.1.20 Registration Error - Program Aborted!
                   13.1.21 This account has expired.
                   13.1.22 Cannot Find LICENSE.TXT!
             13.2  Other problems

        14.0 Standard Disclaimer

        15.0 Contact Information

        16.0 Credits

                           ========================






                                S e n t r y
                                ===========
                     Security for the Home and Business





        1.0 Introduction
        ================

        Currently, almost all fields of computer security are growing
        and advancing, with a few notable exceptions. Networks, servers
        and public access systems are all tightening their access to
        avoid potential problems. But what of the non-networked PC? Is
        the information contained on these any less valuable? Often
        times not, yet adequate security programs do not exist for PC's.
        In my search for security, I discovered that PC's were virtually
        ignored, and those programs that did exist were weak and faulty.
        Faced with this situation, I decided to write my own security
        program from scratch, incorporating the tightest security
        measures possible, while allowing flexible, easy use.


        1.1 Purpose of Sentry

        Sentry is meant for one basic purpose only: to keep unwanted
        people out of "private" information. It is flexible enough that
        this single purpose can be used in many different ways, for many
        different reasons. Here are just a few.

        1.1.1 In the Home

        Most people have something on their home PC that they consider
        to be "sensitive". Maybe it's a private letter, maybe it's
        copies of e-mail, or maybe it's financial information. Or quite
        possibly, you just want a way to keep track of who is using your
        system. Sentry has the solution for all of these problems, by
        restricting access and logging all attempts to use the system.

        Alternatively, sometimes you just want to keep people out,
        period. It could be your nosy room mate, your little brother, or
        your boss at work. In any case, Sentry will keep them out, while
        letting a select group of people in.

        1.1.2 In a Business Environment

        Businesses will find Sentry valuable to guard against
        unauthorized access to PC's. With Sentry, you can leave your
        terminals unattended, knowing that the information held on them
        is secure. Many businesses have cleaners or other independent
        contractors come in during silent hours. A lot of businesses
        have PC's in open areas where a "passer-by" could use them. Most
        terminals are left unattended for a portion of the day (lunch,
        during errands, during meetings, etc.). There's no guarantee
        that an unauthorized person won't attempt to use your PC's when
        you're not around.

        For businesses that work in groups, Sentry is useful for keeping
        track of who used the PC's and when. Supervisors could have
        SuperUser access on all PC's in their group, allowing them to
        manage and control access as required. Also, the log that Sentry
        keeps could be a valuable tool in determining who was doing
        what, and when.

        1.1.3 In an Educational Environment

        Schools and educational institutes will find Sentry useful for
        limiting access to certain terminals. If, for example, only a
        select group of people (staff, administrators, or a certain
        class) should have access to specific PC's, simply give each
        person an account. Anyone without an account cannot log in.
        Sentry will also help track usage, attempted break-ins, and any
        other suspicious activity.

        Often school terminals are left unattended, with nothing to stop
        a student from "poking around." Sentry can act as protection
        from the prying eyes of the student body.

        1.1.4 General

        You may not need to use Sentry on your system. You might never
        have a security problem to worry about. But the truth is that
        Security isn't something to take a chance on. It is a serious
        problem in today's computing society, and many legitimate users
        find themselves helpless or confused about the real issues. It
        is a shame that the immoral few have ruined it for the rest, but
        we cannot let them get in the way of our daily business. With
        the proper tools and knowledge, we can fight back by closing up
        the common loopholes that attackers use.


        1.2 Features of Sentry

        1.2.1 General

        Sentry will allow you to set up accounts on your computer, one
        account for each person you want to have access. If someone
        doesn't have an account, they don't get in. It's that simple.
        Each person has their own account, with their own password,
        making it easy to track who logs in and when. Since Sentry
        doesn't use a "master access" password, you can wipe a single
        users account without affecting any other users.

        Sentry records each login attempt in a log file which can be
        viewed by the SuperUser at any time.

        1.2.2 Expiry Dates

        You can set accounts to expire on a certain date, effectively
        barring access to the specified user after that. For example, if
        you know that Joe will be leaving on April 14th, you can set his
        account to expire on April 15th. That means you don't have to
        remember to delete his account on the 15th... It will expire on
        it's own, and you can delete it whenever you remember.

        You can also set expiry dates for passwords, meaning that a user
        will have to enter a new password once his old one has expired.
        In addition, you can set the period of time that new passwords
        are good for.

        1.2.3 Windows

        Sentry can be used in conjunction with Windows to make it a
        more secure environment. You can protect your MS-DOS icon so
        that only users with an account can drop to DOS. In addition,
        you can tailor the way Windows operates to allow more protection
        from accidental deletion or modification of important items.

        1.2.4 File Protection

        In addition to securing your PC, Sentry can secure individual
        files. If you have a program that you need to keep on your hard
        drive, but you want to restrict who uses it, you can simply
        protect that file with Sentry. A good example of this is the
        FORMAT program. This is a useful command, however you probably
        don't want it available to the masses. The solution? Protect it
        with Sentry. Once protected, only those people you designate
        will be able to execute the program.


        1.3 Distribution of Sentry

        Sentry is a copywritten piece of work, however distribution of
        the ShareWare version is allowed and encouraged. The only
        stipulation is that it must be unmodified, and must contain all
        of the original files (and no others). Essentially, the
        SentryXX.zip file you initially received is the only format that
        Sentry is distributable in.

        DO NOT distribute any registered versions whatsoever. (By
        distributing a registered version, you are giving out copies of
        a specific encoding scheme, which can be used against the
        registered user - and only the registered user!)


        2.0 Setup
        =========

        Since you are reading this, I can safely assume you have
        unzipped Sentry. Along with that, I will also assume that you
        have created a directory for Sentry, and that all Sentry files
        are currently in it. (If this is not true, do it now). You may
        want to read the section entitled "Creating a new Instance of
        Sentry" below.


        2.1 Installing Sentry

        The very first thing you should do is make sure you keep a copy
        of all the Sentry files somewhere safe. Copying them to a floppy
        disk and storing it is a good idea.

        From here, installation is relatively simple. Just run the
        program called INSTALL.EXE. You will now be asked for the
        directory you wish to install to. If it the current directory,
        you can simply enter a period (.) at this prompt. If you enter
        another directory, the files will be copied to that new
        directory, but not deleted from the current one. (You must do
        that yourself).

        If you have previously exported your initialization settings,
        they will be detected now, and you will be asked if you wish to
        use them.

        If there are no exported settings, the install program will
        automatically search to see if your copy of Sentry already has
        initialization settings. If it does, you will be asked if you
        wish to over-write them. Enter 'y' if you wish to overwrite
        them. If you do not already have initialization settings, the
        install program will automatically use the default settings.

        Next you will be asked if you wish to update your system files.
        If you answer 'y' then your AUTOEXEC.BAT, CONFIG.SYS and
        MSDOS.SYS (for Windows 95 only) will be backed up and modified.
        This action will cause Sentry to run automatically the next time
        your computer reboots.

        Finally, you will be asked if you wish to use Sentry with
        Windows. If you answer 'y' then you will be asked for the path
        to your windows directory. You will also be asked a series of
        questions about general Windows security. The options you select
        will automatically be set within windows. If you wish to re-set
        any options, simply run the install program again.

        Please note that the install program deletes itself after
        running. This is so it cannot be run by a regular user to gain
        access or over-write settings. Make sure you keep a backup of
        the install program in case you need it.


        2.2 The Initial Login

        Your first login to Sentry should be as a SuperUser.  This will
        enable you to add yourself as a user and begin customizing your
        installation. It is important that you perform the following
        steps as soon as possible, as leaving the Sentry account is a
        serious security breach.

        As soon as you are ready, run Sentry from the DOS prompt (by
        typing "SENTRY" while in the proper directory). If an error
        message appears, consult section 13.

        To log in as a SuperUser, hold down the CTRL key when pressing
        ENTER, after you have typed in the login "Sentry," without the
        quotation marks.  Then use the password Sentry (sentry or SENTRY
        will not work).  Both login names and passwords are case
        sensitive by default, so remember the capital letters.  You can
        turn off case sensitivity for logins by editing intialization
        settings, but the password will always be case sensitive.

        Now instead of dropping to DOS, or immediately following the
        instructions in your Autoexec.bat file, you will go to the
        SuperUser Menu.

        From here, select "1. User Maintenance Menu."  There you should
        create a new user (you).  You will also want to grant yourself
        SuperUser access.  You can do this by holding down the CTRL key
        while pressing enter after typing the login name. You can also
        use the "Toggle SuperUser Access" menu option to grant SuperUser
        priviliges.

        See the section below on "The SuperUser Menu" for more
        information.


        2.3 First Priorities

        Once you have your account set up, you should delete the Sentry
        account, so nobody else can use it. This is very important as a
        potential intruder will probably try to enter through the
        default Sentry account first. (If you delete it, that closes the
        loophole).

        Sentry will not let you delete the last SuperUser, so you must
        create a new user with SuperUser access before deleting the
        Sentry account.

        From here, you can create the other users of your system, and
        define their starting passwords, expiry dates and access rights.
        See the section below on "The SuperUser Menu" for more
        information.


        2.4 Using the Initialization Settings

        Sentry can be configured to your needs by way of the
        initialization settings. These settings contain information that
        you may wish to change, allowing Sentry to adapt to many
        different situations.

        You can edit the initialization settings from the SuperUser
        menu. You can do this by selecting the "Edit Initialization
        Settings" option (see section 5.10 and section 10 for details).
        Each setting includes helpful hints and information to simplify
        customization. Any changes you make will not take effect until
        the next time you use Sentry.


        2.5 Uninstalling Sentry

        Sentry is simple to uninstall. Simply re-run the INSTALL.EXE
        program (you may have to get it from backup as it deletes itself
        after installing). At the "Install Path" prompt, simply enter an
        asterisk (*) to uninstall.

        From here you will be asked if you wish to remove Sentry from
        your hard drive. Responding with a 'y' will delete the files and
        remove the directory that Sentry is in. Next you will be
        prompted for your windows directory. If you did not install
        Sentry with Windows, you can simply enter an asterisk (*) to
        skip this.

        When the program finishes, Sentry will no longer be on your
        system. If you change your mind, you can re-install it at any
        time.


        3.0 Securing Your Computer
        ==========================

        Sentry is essentially useless unless you take the appropriate
        additional security measures for your machine. Below I have
        outlined some of the things you can do to increase the security
        of your system.


        3.1 BIOS Password

        Protect your BIOS! It has a built in password, so set it!
        Without the password, any user can get into your BIOS and change
        your critical system settings. I have seen several different
        types of BIOS setups, but generally, you use the CHANGE PASSWORD
        command (Sometimes also listed as SUPERVISOR PASSWORD) from the
        main menu and set the SECURITY OPTION to "Setup" (as opposed to
        "System") in the BIOS FEATURES SETUP screen. Depending on the
        layout of your BIOS, you may have a CHANGE SETUP PASSWORD option
        right on the main menu.


        3.2 Boot Sequence

        Change your boot sequence. Again, in your BIOS, under the BIOS
        FEATURES SETUP screen, set your BOOT SEQUENCE to boot from your
        hard drive first. (This usually means set it to C,A as opposed
        to A,C). This will ensure that no-one can bypass Sentry by means
        of a boot disk.


        3.3 SWITCHES in CONFIG.SYS

        This step is not required for Windows 95 users.

        Add "switches /n/f" as the first line of your CONFIG.SYS file.
        The /n will disallow pressing F8 or F5. F8 allows users to step
        through each command of the CONFIG.SYS and AUTOEXEC.BAT files,
        and F5 gives them the option of skipping them all together. This
        means that users cannot bypass Sentry by this method. The /f
        switch is optional, it simply speeds up your boot-up time (by
        about 2 seconds).

        This is automatically done if you update your system files
        through the install program.


        3.4 BootKeys in MSDOS.SYS

        This step is for Windows 95 users ONLY.

        Add the line "BootKeys=0" to your MSDOS.SYS file. This will
        disable the use of F8, F4 or SHIFT to bypass the CONFIG.SYS and
        AUTOEXEC.BAT files. Adding this line is therefore a must,
        otherwise people will be able to defeat Sentry with the press of
        a key. To edit your MSDOS.SYS file, you may need to issue the
        command "attrib -h -s c:\msdos.sys" which will make it readable.
        When you are finished, you should issue the command "attrib +h
        +s c:\msdos.sys" which will restore it to it's previous
        condition.

        This is automatically done if you update your system files
        through the install program.


        3.5 BREAK in CONFIG.SYS

        You must also check your CONFIG.SYS file for any BREAK commands.
        If the command BREAK=ON is present, delete it! This command may
        allow users to break out of the CONFIG.SYS file, which is wrong!
        If BREAK=OFF exists, that is ok (since that is the DOS default,
        and it is secure), however you must get rid of any BREAK=ON
        commands.

        This is automatically done if you update your system files
        through the install program.


        3.6 Passwords

        Pick a good password. Short passwords are a bad idea, as well as
        birthdays, girlfriends names, etc. Anything that is easy to
        guess should be avoided. Good passwords are not words at all,
        but made up from a "mnemonic" sentence. For example, the
        sentence "I'll wait for you" turns into "Illw84u" (trust me).
        Mixing lower case letters, upper case letters, and numbers
        increases the security of a password, and passwords of this type
        are near impossible to guess or crack. Do not write your
        password down, especially near your computer. Try to memorize it
        if possible. Change your password, but not too often. People who
        change their passwords too often (less than 6 months or so) tend
        to write them down, which is a bigger risk. Don't enter your
        password with someone looking over your shoulder. If someone is
        in the room, block their view, or wait until they leave.


        3.7 Placement in AUTOEXEC.BAT

        When you are installing Sentry, make sure it is the FIRST file
        in your AUTOEXEC.BAT! Otherwise, the user may be able to exit
        when another program is running and avoid Sentry all together!

        This is automatically done if you update your system files
        through the install program.


        3.8 Keep a Backup

        Keep a backup copy of all your Sentry files! If something
        happens to these files, you may be locked out your computer if
        you don't have a backup. It is best to copy your entire Sentry
        directory to a floppy disk about once a week, so you won't be
        caught short.


        4.0 Logging In
        ==============

        4.1 The Login Procedure

        When you first run Sentry, you should see the standard startup
        screen. Your registration information is contained here. (The
        shareware release simply says it is registered to Shareware).
        You should also see a prompt asking you to enter your login (or
        user name). If instead you see an error message, check at the
        end of this file for help.

        While entering your user name, if you have SuperUser access, you
        can log in as such. You can do this by holding down the CTRL key
        while pressing enter (CTRL-ENTER). If you do not have SuperUser
        access, or do not wish to log in as such, simply press enter. In
        either case, this will send you to the password prompt.

        Once you have reached the password prompt, you simply enter your
        password, and hit enter when you are finished. Your password is
        not echoed to the screen.

        The minimum and maximum length of both the login and password
        are set by initialization settings. If you wish to change these,
        you must do so from the SuperUser menu.

        After correctly entering your password, Sentry will search for
        any messages addressed to you. If you have a message waiting, it
        will be displayed. Pressing 'd' will delete that message, any
        other key will keep it for the next time you log in. Each
        message is displayed individually.

        Next, the date and time of your last login will be displayed. If
        there have been any invalid login attempts made against your
        account since the last valid login, you will be told so, and how
        many. If the number of invalid login attempts against your
        account has exceeded the maximum allowed, your account will be
        locked out until the SuperUser resets it.

        If your account has expired, it will say so, and subsequently
        lock you out. If your password has expired, it will also say so,
        but will then prompt you to enter a new password. You may not
        re-use your old password, and you must pick a password that
        corresponds to the length limits set out by the initialization
        settings. Once you have entered and verified your new password,
        it is given a new expiry date according to the default (again
        determined by the initialization settings).

        If you have logged in as a SuperUser, and have SuperUser access,
        you will now be in the SuperUser menu (see the section below).
        If not, you will simply be dropped to DOS, and the login
        procedure is complete.


        4.2 Changing Passwords

        If you wish to change your password at any time, you can do so
        by entering the pass key. The pass key is defined in the
        initialization settings, and is displayed when Sentry starts up.
        The default pass key is "passwd". To change your password,
        simply enter your user name as usual, and when prompted for your
        password, enter the pass key. You will then be prompted for your
        old  password (to make sure it is really you), and then you will
        be asked for your new password, which will be verified and saved
        to disk. Your new password will expire in the number of days
        designated by the initialization settings.

        Changing your password has no effect on SuperUser access.


        5.0 The SuperUser Menu
        ======================

        The SuperUser menu is where most of the important actions take
        place. From here it is easy to perform system administrator
        tasks, and maintain user accounts. The following options are
        shown on the SuperUser menu:

            1.  The User Maintenance Menu
            2.  View Log File
            3.  Edit Initialization Settings
            4.  Send a Message to a User
            5.  Protect a File
            6.  Export Initialization Settings
            7.  Exit

        Each option is described below.


        5.1  The User Maintenance Menu

        The User Maintenance Menu contains all actions that affect
        users. The following options can be accessed through the User
        Maintenance Menu:

            1.  Create User
            2.  Delete User
            3.  View Users
            4.  Toggle SuperUser Status
            5.  Change Account Exipry Date
            6.  Change Password Expiry Date
            7.  Change Account Password
            8.  Assign Max Invalid Logins
            9.  Return to SuperUser Menu

        Each option is described below.

        5.1.1  Create User

        This option allows you to create users on your system. First of
        all, you must enter the username (or login) you wish to assign
        to that user. If you wish to create a user with SuperUser
        status, type in the username and hold down the CTRL key when
        pressing enter. Otherwise, just press enter. Once that is
        complete, Sentry asks for the password. The password is not
        echoed to the screen. The user should choose and enter their own
        password. SuperUsers need not know what the passwords are since
        they can still manage the accounts without knowing them. The
        password is entered twice to ensure no typos were made, and then
        saved in encoded form. The ESC key will abort this operation at
        any time.

        Note: There is currently a maximum of 100 users allowed. This
        limit can be bypassed if required (contact me for a larger
        capacity version).


        5.1.2  Delete User

        The delete option is very simple. It brings up a list of all
        users, and you simply use the cursor keys to highlight the user
        you wish to delete. SuperUsers are denoted by a * to the right
        of their username. Press enter to select the appropriate user.
        If the selected user is a SuperUser, Sentry will give a warning.
        SuperUser or not, Sentry will then ask if you are sure you want
        to delete them. Any input other than a 'y' will not perform the
        delete. The ESC key will abort this option at any time.


        5.1.3  View Users

        This option allows you to view all users who currently have
        accounts on your system. SuperUsers are again denoted by a * to
        the right of their login name. The last login date/time, account
        expiry date and password expiry date are also shown to the right
        of the user's login name. In addition, the number of invalid
        logins since the users last valid login are shown with the
        number of invalid logins allowed before an account is locked up.
        An "X" in the "Max Inv Log" (Maximum Number of Invalid Logins
        Allowed) column means there is no limit. You can use the PAGE UP
        and PAGE DOWN keys to scroll forward and back if there are
        multiple pages of users. Arrows will be present if there are
        additional pages above/below. The ESC key will exit back to the
        main menu.


        5.1.4  Toggle SuperUser Status

        When this option is selected, it first brings up a list of all
        users on the system. Again, SuperUsers are denoted by a *. Once
        you have selected a user, Sentry will ask you if you want to
        grant/revoke SuperUser access to/from the appropriate user. Any
        input other than a 'y' will not change that users status. Now
        the user must enter a password. (Since the SuperUser status is
        encoded in the password, and the password can never be decoded,
        I can't change SuperUser access without resetting the password).
        The user can re-enter their old password, or enter a new one
        (the old one will be over-written). In a worst case scenario,
        the SuperUser can re-assign a new password to the user if he is
        unavailable to enter a new password himself. (A hostile user can
        have SuperUser access revoked without having to enter a new
        password; you can do it for him).


        5.1.5  Change Account Exipry Date

        This option lets you define when an account will expire on your
        system. Expired accounts no longer have access. This option is
        useful if a user will be leaving. Then you don't have to
        remember to delete their account on the day they leave. You can
        set it to expire, and delete it when you remember.

        This option also works in conjunction with the "Assign Max
        Invalid Logins" option. Once an account reaches it's maximum
        number of sequential invalid logins, it expires. The only way to
        re-activate the account is to change the expiry date with this
        option.

        Once you select this option, some information about the account
        will be displayed. If it is a SuperUser account, Sentry will
        tell you so. It will then display the account's current expiry
        date. You will be asked if you are sure you want to change that
        user's expiry date. Any input other than a 'y' will abort the
        process, otherwise you will be prompted for the year the account
        will expire. The year must be entered as 4 digits (IE: 1997). If
        you enter 'N' at the year prompt, no expiry date is assigned to
        that account (it is valid forever). If you enter a valid year,
        you will then be prompted for the expiry month, which is entered
        as 2 digits (IE: 06 for June) followed by the expiry day, which
        is also entered as 2 digits. Accounts expire at one second past
        midnight on the date of expiry.


        5.1.6  Change Password Expiry Date

        This option lets you define when a users password will expire.
        Once the password has expired, the user must enter a new one.
        This forces the user to change their password. Once a password
        has expired, the next time the user logs in he will be forced to
        enter a new password. The new password is valid for the number
        of days set by the initialization settings. Once a password has
        expired, the user cannot re-enter it. He must select a new
        password. (NOTE: Sentry does not keep historical records on
        passwords, so a user may alternate back and forth between 2
        passwords. This is not a secure practice and should be avoided).

        Once you select this option, some information about the account
        will be displayed. If it is a SuperUser account, Sentry will
        tell you so. It will then display the current expiry date for
        the password. You will be asked if you are sure you want to
        change that user's expiry date. Any input other than a 'y' will
        abort the process, otherwise you will be prompted for the year
        the password will expire. The year must be entered as 4 digits
        (IE: 1997). If you enter 'N' at the year prompt, no expiry date
        is assigned to that password (it is valid forever). If you enter
        a valid year, you will then be prompted for the expiry month,
        which is entered as 2 digits (IE: 06 for June) followed by the
        expiry day, which is also entered as 2 digits. Passwords expire
        at one second past midnight on the date of expiry.


        5.1.7  Change Account Password

        This option allows the SuperUser to change an account's
        password, in case the user forgot it, or some other strange
        disaster has occurred. When assigning a new password to an
        account, you should set the expiry date to be immediately, so
        the user is forced to choose a new one. If the previous password
        had no expiry date, none is assigned to the new password.
        Otherwise the password expires in the number of days assigned in
        the initialization settings. You can abort at any time by
        pressing the ESC key.


        5.1.8  Assign Max Invalid Logins

        This allows you to set the maximum number of invalid logins
        allowed before an account is disabled. The default number is
        defined in the initialization settings, and is assigned to all
        accounts when they are first used.

        To assign a new maximum, simply select the "Assign Max Invalid
        Logins" option from the SuperUser menu. From here you will be
        shown the complete user list, and asked to select the user you
        wish to change. Pressing the ESC key will abort the operation
        here.

        Once you have selected the user, you will be informed if that
        user is a SuperUser. NOTE: You should not assign a maximum
        number of invalid logins to your last SuperUser account. If you
        do, and someone attempts to break in to that account, you could
        be locked out of the SuperUser menu!

        Next you will be told what the user's current max invalid login
        setting is, and asked if you want to change it. Any input other
        than a 'Y' will abort the operation. Now you will be asked to
        enter the number of invalid login attempts before an account is
        disabled. Entering 'N' or a 0 will mean that there can be
        unlimited invalid login attempts made.

        Please note that a value of less than 10 may cause you more
        trouble than good. You may be spending a lot of time re-setting
        accounts if you pick too low a value, so consider this
        carefully. Also note that when an account is locked up, it is
        actually set to expire immediately. As a result, if you wish to
        re-activate an account, you must change the account's expiry
        date (see above). This is also handy for determining when the
        account was actually de-activated. The expiry date for that
        account it set the day it was locked out.

        Every time a successful login is made to an account, the invalid
        login counter is reset. This means that an account will not be
        locked out if it has a valid login before the maximum is
        reached. (For example, say an account has a maximum of 10
        invalid logins. If there are 7 invalid logins before a
        successful login, and then 5 more invalid logins, the account
        will not be locked up. There must be 10 sequential invalid
        logins for the account to be disabled.)

        Once you have finished making the change, you can view the user
        list to make sure it is acceptable.


        5.1.9  Return to SuperUser Menu

        This option simply returns you to the SuperUser menu. It is the
        same as hitting the ESC key.


        5.2  The Log File Maintenance Menu

        The Log File Maintenance Menu contains all actions required to
        manage the log file. The following options can be accessed
        through the Log File Maintenance Menu:

            1. View Log File
            2. View Backup Log File
            3. Move Log File to Backup
            4. Return to SuperUser Menu

        Each option is described below.


        5.2.1  View Log File

        Every time a user logs in, a record is kept on disk. If you want
        to view that online record, select this option. You will be
        asked if you want view to the log file for one or all users.
        Entering 'o' (for one user) will bring you to the userlist,
        where you can select the user you wish to view. Any other input
        will show the log for all users.

        The log file will be displayed one screen at a time. You can
        press ESC at any time to skip to the end of the file. Once the
        entire log file has been displayed, Sentry will ask you if you
        want to clear the log file. If you were viewing a single user's
        log, Sentry will ask if you want to clear their file.

        Any input other than 'y' will exit, leaving the log file in
        tact. If you answer with a 'y', Sentry will clear out the old
        entries. When viewing the log for all users, that means that all
        entries will be removed. When viewing the log for a single user,
        only that user's entries will be removed.

        The log file itself will not consume much disk space, and so it
        should be left in tact for historical reasons. You may find it
        necessary to refer back to the log file to verify certain
        events. If disk space is a constraint, you can use the "Move Log
        File to Backup" option described later.

        You should always keep a close eye on the log file as this will
        often tell you when something is wrong on your system. All error
        messages are saved to the log file, so you can see if Sentry has
        run into any problems. Also, it records the current time, and
        the username of the user attempting to log in. This will help
        you to identify any potential attacks on your system. The log
        file is hidden by Sentry, but you should also place it somewhere
        safe so that users cannot tamper with it. You can set the
        location of the log file via the initialization settings.


        5.2.2  View Backup Log File

        This option is the same as "View Log File" except it allows you
        to view the information you have backed up. This is strictly for
        historical purposes, so log file information is not lost.


        5.2.3  Move Log File to Backup

        This moves all of the information in the current log file to the
        backup file. The backup file is not overwritten, the new
        information is appended to it. This makes it easier to manage
        when the log file gets large, but you don't want to clear it.


        5.2.4  Return to SuperUser Menu

        This option simply returns you to the SuperUser menu. It is the
        same as hitting the ESC key.


        5.3  Edit Initialization Settings

        This option allows you to edit the initialization settings.
        After installation, it is critical that you go through each and
        every attribute, and make sure it is set to your liking. Many of
        the initialization settings have serious implications on
        security. Once this option is selected, all of the attributes
        are displayed. Simply select the attribute you wish to modify,
        and you will be given the following information:

                - A one line description of the attribute.

                - A brief description of the attribute and it's uses.

                - Valid settings for the attribute, if applicable.

                - Any security notes, if applicable.

                - The default value for the attribute.

                - The current value for the attribute.

        At this time, you will be prompted to enter a new value for the
        attribute. Pressing ENTER on a blank line, or pressing the ESC
        key abort any changes the current value.

        Sentry performs strict checking on the values you enter, and
        will not save an invalid value.

        See section 10 for details on individual settings.


        5.4  Send a Message to a User

        This option allows the SuperUser to send a one-line message to
        any user on the system (including themselves). Once this option is
        selected, you must pick the user you wish to send a message to
        from the list of all users. Once this is done, you will be
        prompted for your one-line message. If you wish to send more
        than one line, simply send two messages to the same user. After
        you have entered your message, you will be returned to the
        SuperUser menu. The next time that person logs in, your message
        will be displayed, including:

          - Who the message is from
          - The time and date the message was sent
          - The message itself

        The user then has the option to delete the message. If they do
        not delete the message, they will also see it on their next
        login.

        NOTE: Messages are displayed before any login information, so
        you can send messages to users that are locked out. That way, if
        you wish to send an explanation, you can.


        5.5  Protect a File

        This option allows you to protect executable files (.EXE, .COM
        and .BAT). When this option is selected, it prompts for the file
        name. You must enter a path to a file that exists, and the file
        must be executable. If the file name is correct, Sentry then
        processes that file, and "protects" it. Protection means that
        the next time that file is run, Sentry will execute. If the user
        enters a valid login and password, then the original file
        executes. If not, then the file is not executed.

        This is useful for protecting individual files. After all, if a
        person successfully logs into your computer, they have free
        access to anything there. This will allow you to tighten up
        access to individual files.

        The current method of protection does not work with all files.
        That is to say, I have tested it on some files that do not run
        correctly once protected. (It seems to be memory or video
        conflicts). Currently, a protected file has about 100k less
        memory available to it than if it was run normally. Also,
        protecting programs that run within Windows does not work. These
        issues are "on the list" for research.

        See section 7 for specific details on protecting files.


        5.6  Export Initialization Settings

        Selecting this option will export the Initialization Settings.
        This will allow you to use the same settings and account
        structure when you upgrade. The process for this is simple.
        Select this option, and it will export the settings. Now simply
        unzip the new SentryXX.zip into your directory (overwriting all
        files), and run the Install.exe program. Install will
        automatically sense the exported information, and ask if you
        want to use it. If you say yes, the settings are automatically
        updated to the new version, and loaded in.

        Please note that you should not export the settings unless you
        plan to import them right away into a new version (it can cause
        a slight security risk).


        5.7  Sentry DOS Shell

        Selecting this option temporarily drops the SuperUser to a DOS
        shell where they can execute any normal DOS commands. This shell
        has limited memory and environment space, and should only be
        used for simple file maintenance. Do not attempt to run any
        large or complicated files while in the DOS shell.

        Type "EXIT" to return to the SuperUser menu.


        5.8 Security Audit

        This is one of the more powerful options in Sentry. Selecting
        this option will cause Sentry to automatically search for
        weaknesses in your setup. The audit searches in three main
        areas:

            - Your System
            - Your Initialization Settings
            - Your Account Structure

        As each of these sections is tested, the user will be informed
        of Sentry's findings. If a section has no weaknesses detected,
        then an "Ok" will appear. Otherwise, Sentry will describe the
        weakness, and ask if you want to fix it. Pressing 'y' will
        either fix the problem automatically, or prompt you for a new
        value, depending on the situation.

        In each section, the following items are checked during an
        audit:

            System

            Check for the following:
            - no "switches" line in CONFIG.SYS (non-Win95 only)
            - no "BootKeys" line in MSDOS.SYS (Win 95 only)
            - no call to Sentry from the AUTOEXEC.BAT file
            - a "break on" command in the CONFIG.SYS file

            Initialization Settings

            Check for the following:
            - a short max or short min password length
            - a high number for maximum login attempts
            - a low number for wait delay
            - password echoing should be off or masked
            - a password expiry max of over 365 days
            - an unused account expiry max of over 365 days
            - a long wait for the screen saver (over 600)
            - case sensitivity is off

            Accounts

            Check for the following:
            - accounts that have expired
            - SuperUser accounts with a max inv log setting
            - normal accounts with no max inv log setting
            - accounts where the number of failed login attempts is
                exceeded
            - accounts with no expiry date
            - passwords with no expiry date

        As a SuperUser, you should run the audit frequently. If all is
        well, it completes in a few seconds, but it can alert you to
        potential problems or suspicious activity that you might not be
        aware of otherwise.

        The message "Audit Complete" will appear when the audit is
        finished. At this point, the user may press any key to return
        to the SuperUser menu.


        5.9  Exit

        This simply returns you to the DOS prompt. It is the same as
        pressing the ESC key.


        6.0 Using Sentry With Windows
        =============================

        6.1 General

        Sentry is also adaptable to Windows, allowing you to keep users
        away from DOS. This may be desirable if you enter Windows
        immediately upon startup (I.E.: your AUTOEXEC.BAT contains "win"
        as a command). If you want to limit access to your system as a
        whole, you could install Sentry in the usual way. This would
        keep out unwanted users all together. If you want to also limit
        access to the DOS prompt from Windows, you can do that too. All
        you must do is create a new instance of Sentry (see below), and
        then simply set up your windows to run Sentry when you drop to
        DOS. The example setup below assumes you have installed an
        instance of Sentry in c:\Sentry\Inst1, but you can substitute
        your actual directory names in where applicable.


        6.2 Installation Procedure

        Installing Sentry in the Windows environment is simple. Included
        in the Sentry zip file are 2 files:

        Sentry.grp
        Sentry.pif

        Both of these will be copied to your windows directory during
        the install. Enter Windows and from the Program Manager, select
        [F]ile, then [N]ew. Next select Program Group. When prompted,
        enter "Sentry" for both description and file name. Now you
        should see a new program group called Sentry. The Sentry program
        group should contain a single icon, labeled MS-DOS. This icon
        actually points to sentry.pif, which contains specific
        information about running Sentry.

        You can edit the new icon (highlight it and press ALT-ENTER) and
        change the working directory to point to your Sentry files.

        IE: c:\Sentry, or c:\Sentry\Inst1, etc.

        From here, run the Pif Editor program (the icon is a little
        tag), and open Sentry.pif. Now change the "Program Filename" to
        point to your Sentry.exe file.

        IE: c:\Sentry\Sentry.exe, or c:\Sentry\Inst1\Sentry.exe, etc.

        In Addition, change the "Working Directory" to be the same as
        the working directory for the icon (see above). Once you save
        the .pif file, you are all set.

        At this point you should test out the new Sentry icon to make
        sure it works ok. When you double click on the new icon, it
        should take you directly to Sentry. Once you have entered a
        correct username and password, it will then drop you to a
        regular DOS shell. You can type "EXIT" to return to Windows at
        any time.

        Once you are sure it works, remove your old MS-DOS icon, so that
        users cannot use it to drop straight to DOS. You can drag your
        new icon into the same location as your old MS-DOS icon, so
        everything will look the same.

        Now there is one last step. If a user were to exit Windows, they
        would be at the DOS level, which is not what we want. Since your
        AUTOEXEC.BAT file is running windows on startup, you can block
        people from exiting by forcing them to go through Sentry. You
        can do this by adding a call to Sentry after the win command in
        your AUTOEXEC.BAT.

        For example, the last lines of your AUTOEXEC.BAT might look like
        this:

        ----------------- CUT ----------------
        win
        \Sentry\Inst1\Sentry
        ----------------- CUT ----------------

        Alternatively, you can add the security measures offered by the
        install program.

        If it seems like a complicated process, just try the steps one
        at a time, and make sure everything works ok. The end result is
        that when you click on the MS-DOS icon, it will run Sentry
        before dropping you to the DOS shell. That means that you can
        limit access to the operating system, without pulling any fancy
        tricks in Windows. Since you have made a new instance of Sentry,
        you could have one instance run when you boot up (giving access
        to windows), and have another instance run when you click on the
        DOS icon (giving access to the operating system). That way, a
        user that has access to your PC may not be able to drop to DOS.

        Be warned that Sentry will still lock up your terminal if a user
        fails to log in. If this happens in Windows, you may be able to
        recover back to Windows by pressing CTRL-ALT-DELETE and closing
        the DOS prompt. This will still not allow access to DOS, but you
        will not lose anything you were working on.


        6.3 Windows 95

        Sentry is easily adaptable to use in a Windows 95 environment.
        In most respects, the setup is the same as in a DOS/Windows
        environment.

        The primary difference with Windows 95 is instead of adding the
        line "switches /n/f" to your CONFIG.SYS file, you must add the
        following line to your MSDOS.SYS file:

        BootKeys=0

        This will disable the use of F8, F4 or SHIFT to bypass the
        CONFIG.SYS and AUTOEXEC.BAT files. Adding this line is therefore
        a must, otherwise people will be able to defeat Sentry with the
        press of a key. To edit your MSDOS.SYS file, you may need to
        issue the command "attrib -h -s c:\msdos.sys" which will make it
        readable. When you are finished, you should issue the command
        "attrib +h +s c:\msdos.sys" which will restore it to it's
        previous condition.

        As before, ensure that the call to Sentry is at the beginning of
        your AUTOEXEC.BAT file. The Sentry.pif file and Sentry.grp file
        will still work with Windows 95, although at this time I have
        not drawn up specific instructions for installation.

        I have not yet conducted thorough tests in a Windows 95
        environment, however documentation for this should be
        forthcoming in a future revision.


        7.0 Securing Other Programs
        ===========================

        7.1 General

        In some cases, it might be beneficial to secure a single
        program. It might be a word-processor, Windows, or a potentially
        dangerous file like FORMAT.COM. In any case, you can secure it
        with Sentry, even if you don't use Sentry during boot-up.


        7.2 Setup

        To successfully protect your file, you must keep a backup.
        (Sentry cannot reverse the process of protecting a file!) This
        backup should not be kept anywhere accessible (IE: make a backup
        on floppy, and store it somewhere safe). After all, if a user
        can run an unprotected version of the file, why bother
        protecting it in the first place? It is wise to test the file
        once it has been protected to ensure it works as expected.

        To protect a file, simply chose "Protect a File" from the
        SuperUser menu. Sentry will ask for the file name of the file to
        protect. The file must be an executable (IE: it ends with .EXE,
        .COM or .BAT). Batch files are automatically converted into .EXE
        files. Once you have entered a correct file name, Sentry will
        then proceed to protect the file. When it is finished, you will
        be returned to the SuperUser menu. Your file is now protected!

        The applications for this type of protection are almost
        limitless. Use your imagination. If you come up with an
        innovative idea, I would be interested in hearing about it.


        7.3 Account Information

        The account structure for a given protected file is copied from
        the version of Sentry that protected the file, but is unique.
        That is, once a file is protected, a SuperUser can
        add/delete/modify any accounts for that protected file without
        affecting any other copies of Sentry. The initialization
        settings are treated in the same manner. Each protected file has
        their own unique copy.

        To change account information on a protected file, simply run
        the file, and when Sentry executes, log in as a SuperUser. You
        can now perform all SuperUser options as usual.


        7.4 Using Templates

        It is possible to set up "template" instances of Sentry for use
        when protecting files. This can be extremely useful as it saves
        the administrator a considerable amount of time, as well as
        decreasing the possibility of making a mistake.

        To use templates, you must set up several instances of Sentry
        (one for each template you wish to use). See section 8 for
        instructions on how to create an instance of Sentry.

        A sample setup could be as follows:

        c:\Sentry
             |
             +----+------- Private
                  |
                  +------- Public
                  |
                  +------- SemiPub

        With each instance having a complete copy of Sentry. Next simply
        modify the account structure of each instance to match the
        template. That is, the Private instance would contain only the
        SuperUser(s), the Public may contain all users, and the
        Semi-Public would contain the SuperUser(s) plus some users.

        Now you would use the Private instance as a template to protect
        exclusive executables, such as format.com. When you use the
        Private template, the protected file is automatically set to
        allow only SuperUsers to run it.

        Similarly, the Semi-Public template can be used for programs
        that only the SuperUser and a select number of users have access
        to.

        The advantage to using templates is that the administrator need
        only set up the account structure and initialization settings
        once. From that point forward it becomes the default for all
        files protected using that template.


        7.5 Running a Protected File

        To use a protected file, simply run it as usual. Now, instead of
        the program executing, Sentry will run. The user will be
        confronted with a login prompt, and they must enter a correct
        login and password to continue.

        An unsuccessful login will result in the user being locked out
        (as with Sentry in normal use). A successful login will simply
        run the protected file. Once the file is run, the user will be
        returned to whatever they were doing (IE: the DOS prompt, etc).

        Command line arguments are passed to protected files in the same
        manner as usual. To run the file FORMAT with the argument A:, it
        would look like this:

        format a:

        which is identical to the usual way of passing command line
        arguments.


        8.0 Creating a new Instance of Sentry
        =====================================

        In some of the scenarios listed above, you may be required to
        create a new "instance" of Sentry. That is to say, a completely
        new copy of Sentry, that works independently of all other
        copies. This is a fairly simple process, that you can perform as
        many times as required.

        The first thing you must do when creating a new instance is to
        create the directory you wish to place it under. If you plan to
        have several instances, you may want to create a Sentry main
        directory, with your instances branching off of that. For
        example:

        c:\Sentry
             |
             +----+------- Inst1
                  |
                  +------- Inst2

        This will allow you to keep all your Sentry files well
        organized, and separate from your other programs. Create a
        directory for each instance you anticipate you will need. From
        there, simply copy ALL of the Sentry files into each directory.

        The final step is to set up the accounts of each instance
        according to your needs. To do this, you must go into each
        directory individually and run Sentry. Now log in as a SuperUser
        and set up all the required accounts. Remember that each
        instance is independent of the others. Your account information
        will not be the same for any 2 instances (otherwise there is no
        advantage to having 2 instances).

        You should always test out each instance and make sure it works
        before using it.


        9.0 Registration
        ================

        9.1 General

        If you use Sentry on your machine(s), I urge you to register. A
        lot of time and effort has been put into Sentry to make it a
        viable security program. With your help, Sentry can continue to
        adapt to new situations and keep abreast with any new
        developments in the field of computer security.

        On the other hand, I realize that not everyone can afford to
        register. In that case, please feel free to continue to use the
        ShareWare version. There are no limitations on how long or how
        many times it can be used. My intention with Sentry was to make
        a contribution to PC security, and to make it available to
        everyone. All I ask is that if you use Sentry, and are able,
        please register.

        The shareware version of Sentry has all the functionality of the
        registered version, with one exception: it does not encode
        passwords. This will allow you to test out all the functions of
        Sentry before you commit to purchasing it. The ShareWare version
        in itself is a very secure program as is, however if you are
        serious about security, plaintext passwords are not a viable
        option.

        To order, simply fill out the order form provided (Order.frm)
        and e-mail or snail-mail a copy to me.


        9.2 Benefits of Registration

        As a registered user, you will receive:

              - The full Sentry program (with password encryption) and
                related files on 3.5" disk.

              - A laser printed user's manual (essentially this file,
                with a few changes in format and content).

              - Online internet support via e-mail.

              - Free upgrades as soon as they are available via the
                internet.

              - Notices about any potential security risks, and
                instructions on how to protect yourself.

              - The ability to request specific features in future
                versions of Sentry.

              - A clear conscience knowing that you paid for your
                software.

        NOTE: Registered versions are not inter-compatible. That is,
        user X's account information is encrypted differently than user
        Y's. The version of Sentry that you receive is good only for you
        and your files. (Likewise, nobody else can use their copy of
        Sentry with your account information). See the order form for
        information on obtaining compatible versions of Sentry.


        10.0 The Initialization Settings
        ================================

        Shown below are all of the initialization settings that may be
        changed within Sentry. A short description of each setting is
        included, as well as any security notes, and the default
        setting.

        10.1 Location of the Log File

        This contains the location of the log file. The log file should
        be kept somewhere safe, tucked away from prying eyes.

        NOTE: You should change the name of the file from Sentry.log to
        some other, inconspicuous name. Potential intruders will search
        for the Sentry.log file. You can hide it under misleading names
        such as file_id.diz, chklist.ms, warm.com etc etc.

        Default: c:\Sentry.log


        10.2 Location of the Backup Log File

        This contains the location of the backup log file. When the max
        log file size has been reached, half of the log file is
        automatically moved to the backup log file. This prevents the
        primary log file from getting too large.

        Default: c:\backup.log


        10.3 Location of the Message File

        This contains the location of the message file. The message file
        should be kept somewhere safe, tucked away from prying eyes.

        NOTE: You should change the name of the file from Sentry.msg to
        some other, inconspicuous name. Potential intruders will search
        for the Sentry.msg file. You can hide it under misleading names
        such as file_id.diz, chklist.ms, warm.com etc.

        Default: c:\Sentry.msg


        10.4 Minimum Password Length

        Sets the minimum length for passwords and logins.

        NOTE: A value of 4 should be the absolute minimum for
        MinPasswordLen. A value of 5 or 6 would be even better. Short
        passwords are much easier to stumble across since less attempts
        have to be made before it is guessed.

        Default: 4


        10.5 Maximum Password Length

        Sets the maximum length for passwords and logins.

        Default: 20


        10.6 Maximum Invalid Tries

        Sets the maximum times a user can attempt to log in before being
        locked out.

        NOTE: This should not be set too high. It is very rare for a
        legitimate user to botch a login attempt 3 times in a row. A
        potential intruder will usually have to make many attempts
        before getting anywhere. Setting MaxTries to around 3 will slow
        him down greatly, as he will have to reset after 3 failed
        attempts.

        Default: 3


        10.7 Wait Time After an Invalid Login

        Sets the delay in seconds to wait after the user fails to log
        in.

        NOTE: Setting the WaitTime to 3 or above greatly slows any
        methodical attempt to guess or discover passwords. It offers
        little inconvenience to the end users while providing added
        security.

        Default: 3


        10.8 Max Log File Size

        This sets the maximum size the log file can reach before the
        oldest half of it is automatically moved to the backup log file.
        The size is given in number of kilobytes (1024 bytes). A value
        of 0 means never backup the log file.

        Default: 20


        10.9 Key to Change Password

        Sets the "key" to enter as a password to change passwords.

        Default: passwd


        10.10 Password Echo Character

        Sets the character to be echoed to the screen when the password
        is being entered.

        Enter '?' to display no character.
        Enter '!' to display the actual character (not recommended).

        Default: *


        10.11 Days Until Passwords Expire

        Sets the number of days a password is good before it expires.
        This is the Default value used whenever a password is changed.
        Individual passwords can be set to expire on the SuperUser menu.

        NOTE: It is a good idea to have this set to between 180 and 365.
        Anything over a year is a security risk due to age. Anything
        under half a year is a risk because people will tend to forget
        their passwords and start writing them down. This setting should
        depend on how busy your system generally is.

        0 = Never expire passwords.

        Default: 365


        10.12 Days Until Accounts Expire

        Sets the number of days an unused account is good before it
        expires. This is the Default value used whenever an account is
        created. Individual accounts can be set to expire on the
        SuperUser menu.

        NOTE: This setting should depend on the level of activity on
        your system. Active systems can afford to have a lower setting
        than generally inactive settings. You should also take into
        consideration the probability of an intruder using an old
        account.

        0 = Never expire unused accounts.

        Default: 365


        10.13 Screen Saver Activation Time

        This sets the amount of idle time (in seconds) that may pass
        before the screen saver is activated.

        Default: 300


        10.14 Screen Saver Message

        This is the message that is displayed randomly on the screen
        when the screen saver is active.

        Default: This is a Secure Terminal.


        10.15 Login Prompt

        This sets the value of the prompt that is displayed when the
        user is expected to enter their login name. Modifying this
        allows you to customize your environment as you see fit.

        Default: Login:


        10.16 Password Prompt

        This sets the value of the prompt that is displayed when the
        user is expected to enter their password. Modifying this allows
        you to customize your environment as you see fit.

        Default: Password:


        10.17 Wrong Password Message

        This sets the message to be displayed when a user enters the
        wrong password.

        NOTE: It is a good idea to keep the wrong password and wrong
        login messages the same. Otherwise, a potential intruder will
        know when he has found an account (IE: If Sentry responds with
        "Invalid Password", he knows the login was correct). Keeping the
        two the same prevents an attacker from knowing if he even has
        the correct login.

        Default: Invalid Login.


        10.18 Wrong Login Message

        This sets the message to be displayed when a user enters the
        wrong login.

        NOTE: It is a good idea to keep the wrong password and wrong
        login messages the same. Otherwise, a potential intruder will
        know when he has found an account (IE: If Sentry responds with
        "Invalid Password", he knows the login was correct). Keeping the
        two the same prevents an attacker from knowing if he even has
        the correct login.

        Default: Invalid Login.


        10.19 Bad Password Length Message

        This sets the message to be displayed when a user enters a
        password of invalid length.

        NOTE: It is wise to keep the wrong password length, wrong login
        length, wrong password and wrong login messages the same. This
        will prevent a potential attacker from knowing the max and min
        settings for passwords or logins on your system. (Knowing the
        length of a password can greatly decrease the amount of time
        required to crack it).

        Default: Invalid Login.


        10.20 Bad Login Length Message

        This sets the message to be displayed when a user enters a login
        of invalid length.

        NOTE: It is wise to keep the wrong password length, wrong login
        length, wrong password and wrong login messages the same. This
        will prevent a potential attacker from knowing the max and min
        settings for passwords or logins on your system. (Knowing the
        length of a password can greatly decrease the amount of time
        required to crack it).

        Default: Invalid Login.


        10.21 Wrong Password Log Message

        This sets the message to be saved to the log file when a user
        enters the wrong password.

        Default: User entered the wrong password.


        10.22 Wrong Login Log Message

        This sets the message to be saved to the log file when a user
        enters the wrong login.

        NOTE: This message should be descriptive, since the SuperUser
        will use it to determine what sort of activities have been
        happening.

        Default: User entered the wrong login.


        10.23 Bad Password Length Log Message

        This sets the message to be saved to the log file when a user
        enters a password of invalid length.

        Default: Invalid Password Length.


        10.24 Bad Login Length Log Message

        This sets the message to be saved to the log file when a user
        enters a login of invalid length.

        Default: Invalid Login Length.


        10.25 Environment Variable

        This sets the environment variable used to store the user's
        login name after a successful login.

        NOTE: The environment variable USER is used by many networks,
        such Novell. By using this setting, Sentry can be used in
        conjunction with these networks.

        Default: USER


        10.26 Enable Sentry with Windows

        The Windows flag is set if you wish to run Sentry from Windows.
        Technically, this allows Sentry to open up a DOS shell after a
        successful login. Setting this option to 1 has no effect on
        normal use, and is not a security risk.

        (0=Do Not Run In Windows, 1=Run In Windows)

        Default: 1


        10.27 Show Title

        This determines if the intro screen is displayed or not. You may
        choose not to display the title information if you don't want
        users to know what program you are using. On the other hand, the
        registration information should be displayed for authenticity's
        sake. I have added this option because security comes before all
        else.

        (0=Not Displayed, 1=Displayed)

        Default: 1


        10.28 Date Format

        This will allow you to have dates displayed in different
        formats. Some people prefer different formats than others, so
        this will allow you to define the way dates are displayed.

        (0=MM/DD/YYYY, 1=DD/MM/YYYY)

        Default: 1


        10.29 Case Sensitivity

        This sets the case sensitivity. If "Case Insensitive" is
        selected, "SENTRY" "sentry" and "Sentry" are all treated as the
        same at the login prompt. If case sensitivity is enabled, the
        three are all treated as different logins.

        (0=Case Sensitive, 1=Case Insensitive)

        NOTE: Using "Case Insensitive" reduces the number of allowable
        logins, and increases the probability of an attacker getting a
        correct login. Still, some people find it easier to work with
        Case Sensitivity off.

        Default: 0


        10.30 Windowed Mode

        This allows you to use Sentry in a "windowed" mode (not to be
        confused with Microsoft Windows). If the windowed mode is
        undesirable, you can choose not to use it.

        (0=Regular Mode, 1=Normal Windowed Mode, 2=Exploding Windowed Mode)

        Default: 2


        10.31 Enable Colour

        This determines if colour will be displayed by Sentry or not.
        Some laptop users may wish to use the black and white setting
        for better readability.

        (0=Black and White, 1=Colour)

        Default: 1


        10.32 Text Colour

        You can set TextColour to the value of the colour you wish
        normal text to appear in. Colour values are shown in the chart
        below.

        COLOURS:
        0 Black 4 Red        8 Dark Gray    12 Light Red
        1 Blue  5 Magenta    9 Light Blue   13 Light Magenta
        2 Green 6 Brown      10 Light Green 14 Yellow
        3 Cyan  7 Light Gray 11 Light Cyan  15 White

        Default: 15


        10.33 Text Background

        You can set TextBackground to the value of the colour you wish
        normal text to have as a background. Colour values are shown in
        the chart below.

        COLOURS:
        0 Black 4 Red
        1 Blue  5 Magenta
        2 Green 6 Brown
        3 Cyan  7 Light Gray

        Default: 1


        10.34 Highlighted Text Colour

        You can set HighColour to the value of the colour you wish
        highlighted text to appear in. Colour values are shown in the
        chart below.

        COLOURS:
        0 Black 4 Red        8 Dark Gray    12 Light Red
        1 Blue  5 Magenta    9 Light Blue   13 Light Magenta
        2 Green 6 Brown      10 Light Green 14 Yellow
        3 Cyan  7 Light Gray 11 Light Cyan  15 White

        Default: 1


        10.35 Highlighted Text Background

        You can set HighBackground to the value of the colour you wish
        highlighted text to have as a background. Colour values are
        shown in the chart below.

        COLOURS:
        0 Black 4 Red
        1 Blue  5 Magenta
        2 Green 6 Brown
        3 Cyan  7 Light Gray

        Default: 7


        10.36 Maximum Invalid Logins

        This sets the Default number of consecutive invalid logins
        possible before an account is locked out. Only a SuperUser can
        subsequently unlock an account.

        Default: 10


        10.37 Type Ahead

        This allows you to determine if Sentry acknowledges characters
        typed before execution began. With this option enabled, the user
        can type their login and password before Sentry runs, and it
        will automatically be used. This is useful for saving time while
        logging in.

        (0=Ignore input, 1=Accept input)

        NOTE: Some System Administrators turn this option off because it
        can cause some users to get confused and log in incorrectly.

        Default: 1


        10.38 Clear Screen

        This setting determines if the screen is cleared before running
        Sentry. Some users prefer to turn this option on as the screen can
        look cluttered otherwise.

        (0=Don't clear screen, 1=Clear screen)

        Default: 0


        11.0 Technical Notes
        ====================

        11.1  Encoding Algorithm

        The encoding algorithm used is the standard UNIX Crypt()
        algorithm. It is a one-way encoding algorithm that incorporates
        the Data Encryption Standard (DES) and RSA technology. It is
        used on UNIX systems to secure passwords. (As a note, the
        encryption code is not included with the ShareWare version, so
        no amount of examining the code will reveal the algorithm).

        The users' passwords are never decoded. They are stored on disk
        and in memory in an encoded format. The entered passwords are
        encoded using the same algorithm and matched in an encoded form.
        This prevents disk or memory scans from revealing the password
        to prying eyes.

        I have begun running some tests on cracking the passwords, and I
        will include my results. So far, this is what I have found:

        Password Length          Maximum Time to Break
        ------------------------------------------------
        4                        22 days
        5                        1368 days or 3.75 years
        6                        232.4 years
        7                        14409 years
        8                        893357 years

        All times listed are approximated as using a Pentium 90MHz CPU
        and an alpha-numeric password.

        These figures may be adjusted as my testing becomes more
        accurate. The above figures also assume you know the length of
        the password, which cannot be determined by looking at the
        encrypted version. As a result, the search time may be much
        greater.


        11.2  SuperUser Access

        SuperUser access is also encoded in the password. I tried many
        different ways before finally settling on this. It is the most
        secure method. Actually, SuperUser access is stored on the
        password (which is then encoded), and then stored again on the
        encoded password. That looks like:

        password                      <-- Password as entered.

        super(password)               <-- Password with SuperUser stamp.
                                          * This is the stamp that is
                                          used to determine access.

        crypt(super(password))        <-- Encoded password with
                                          SuperUser stamp.

        super(crypt(super(password))) <-- SuperUser stamped encoded
                                          password with SuperUser stamp.
                                          * This is the stamp that is
                                          used to "see" who has
                                          SuperUser access.

        That way when you use the "View Users" command, you can see
        which ones are SuperUsers. However, since the non-encoded
        SuperUser stamp can be edited, it is only used for viewing. The
        encoded SuperUser stamp is used for access. If anyone attempts
        to alter the SuperUser stamp, a warning will be displayed in
        the log file each time that user logs in.


        11.3  Files

        The following files are included with this release of Sentry:

        Sentry.exe      This is the executable program.
        Install.exe     The installation program.
        File_id.diz     Short description file.
        History.txt     The complete revision history of Sentry.
        License.txt     The license agreement.
        Order.frm       The order form.
        Qstart.txt      Quickstart instructions.
        Readme.com      Displays this file.
        Readme.txt      This file.
        Sentry.ins      Descriptions of Initialization Settings.
        Sentry.hlp      Sentry's Help file.
        Sentry.grp      The Sentry Group file for Windows.
        Sentry.pif      The Sentry .pif file for Windows.
        Whatsnew.txt    A short description of modifications to the
                        latest version.

        If you do not have all of these files, Sentry may not work for
        you. You can pick up a complete copy of Sentry (and updates as
        they become available) at:

              http://dragon.acadiau.ca/~910318b/Sentry.html


        11.4  File_id.diz

        The actual contents of the file_id.diz file are shown below. If
        any modification has been made to the original file, please
        re-create it from the following section.

        NOTE: this is primarily for SysOps of BBS's. Single users can
        delete the file_id.diz if they wish. (However, please make sure
        that all files are present if you distribute the program.)

        -------------------CUT-----------------------
        (V5.0) Sentry - Security for DOS/Windows/95.
        Sentry is an extremely flexible program that
        allows you to secure your system, individual
        files,  Windows, Win 95 or any combination.
        It supports up to 100 users with normal and
        "SuperUser" access. Detailed log files help
        keep track of activity. Expiry dates and a
        mini message system help with user admin.
        http://dragon.acadiau.ca/~910318b/Sentry.html
        Mike Bobbitt [Mike.Bobbitt@@AcadiaU.Ca]
        -------------------CUT-----------------------


        11.5  Time / Date

        NOTE: I have found one date which always seems to cause an
        error. 01/01/1997 translates to 01/15/1995 (1st day of the 15th
        month of 1995). This is obviously incorrect. I have determined
        it is a bug in Borland's date conversion routines. It is the
        ONLY date that causes problems, to my knowledge, all others
        translate fine. I advise against using 01/01/1997 for any expiry
        dates.

        This problem is still under investigation.


        11.6  Environment Variables

        When a user successfully logs in, a DOS environment variable is
        set to that user's login name. This can be a very useful feature
        as it allows custom programs to link with Sentry in a meaningful
        way.

        For example, if you are running Sentry from a batch file, you
        can check to see who logged in, and take appropriate action.

        Shown below is a short batch file which can be used for this
        type of function:

        -----------CUT-----------
        @@echo off
        rem *** Run Sentry.
        c:\sentry\sentry
        rem *** Test to see who logged in.
        rem *** Use the user's login name for the line below.
        rem *** It must be UPPERCASE.
        if %user==MIKE goto mike
        if %user==DANNY goto dan
        rem *** Use a line like the one above for each user.
        goto end
        :mike
        rem *** Note that individual users have their own commands.
        echo SuperUser logged in.
        defrag c:
        rem *** Other commands here
        goto end
        :dan
        echo Dan logged in.
        goto end
        rem *** Add more users as you see fit
        :end
        rem *** Add the commands here that will be executed by
        rem *** everyone, regardless of their login.
        -----------CUT-----------

        NOTE: Batch files are not secure! No critical functions should
        be placed here unless it's absolutely necessary!

        An alternative (and more secure) method is to write a program in
        another language (like C) and compile it. Most programming
        languages allow you to read environment variables. This means
        that you can write your own custom extensions to Sentry, which
        will execute after a person logs in.

        Please also note that the usernames in the environment variables
        are all capital letters. (Sentry becomes SENTRY when it is set).

        ** NOTE: Although the environment variables are secure
        immediately after Sentry runs, they may not be secure after
        other programs have run. By this I mean that another program
        could alter the environment variables to make it LOOK like a
        different user logged in. As a result, try to do all your
        checking immediately after Sentry runs.


        11.7  Virus Scanners

        If you scan your system with a virus scanner such as Microsoft
        Anti-Virus, you may find that Sentry will show up quite often.
        The reason for this is that some virus scanners record
        statistics on executable files. When the next scan is performed,
        if the executable files do not match the statistics, the scanner
        panics. This can SOMETIMES be evidence of a virus on your
        system. Sentry modifies itself (in a manner similar to
        a virus) and so may be picked up on occasion, however please be
        aware that there is no threat from Sentry.

        SENTRY IS NOT A VIRUS!

        Every time you use Sentry, the executable is modified, and will
        cause your virus scanner to panic! Do not be alarmed, since this
        is normal operation for Sentry.


        11.8  File Deletion

        Many times, sensitive information can be obtained by recovering
        deleted files and examining their contents. This is a common
        practice, and takes little technical skill to achieve. An
        unauthorized user "undeleting" files can cause the System
        Administrator a lot of hassle if the information recovered is
        sensitive. Also, the user may be able to study the information
        and devise a plan of attack based on how the system operates.

        As such, when Sentry deletes a file, that file cannot be
        "undeleted" to recover any sensitive information. Sentry
        achieves this by routing all delete requests through a special
        function. This function essentially fills the target file with
        garbage (random characters) before deleting it. Once deleted,
        the target file may be "undeleted" however the only information
        available from the recovered file is the garbage, not actual
        data. As a result, an unauthorized user will not be able to
        recover anything more than random characters from Sentry's
        execution.

        Sentry uses this method of deletion on all files, regardless of
        their level of sensitivity. Please note however that deleting a
        file at the DOS prompt, or through any other program does not
        use this secure method.


        11.9  General

        Sentry is written in Borland C, with sections of C++. As of
        version 5.0, Sentry contains over 7000 lines of code.
        Portability between machines is not an issue, since Sentry has
        been designed and tested on standard MS-DOS machines.

        Sentry is verified compatible with Windows 3.x and Windows 95.


        12.0 Potential Threats To Security
        ==================================

        Never underestimate your users. And never be satisfied that your
        system is completely "air-tight". Users are incredibly apt at
        finding loopholes in security, and once found, these holes can
        be exploited. Because of this, I am listing below all of the
        security loopholes that I am aware of at this time.


        12.1 Account Information

        With the release of Sentry V3.0, account information has become
        much more secure. It is still POSSIBLE however that a user can
        find and dissect the account information. The probability of
        this is remote though, since the information is not easily
        edited or understood. Also, all of these methods require a
        working knowledge of how Sentry operates, and that is not
        commonly available. The best source for that information would
        be from this file, which is deliberately missing some key pieces
        of "technical" information.

        If a user did manage to decipher the account information, he may
        be able to do any of the following:

        - Add/Remove an expiry date (account or password)
              This is not a serious issue for passwords, as the user
              would still have to enter their old one before being
              notified that their password has expired. An attacker can
              NOT expire a password and then log in to that account.

        - Edit a username
              This would effectively lock out that user, unless they
              could guess their new user name.

        - Delete a user
              Users can be deleted, but not created.

        - Destroy a password
              Since passwords are encoded, there is no way to change a
              password to something usable. An edited password will lock
              that user out of their account, until the password is
              reset.

        - Change "last login" information
              Not critical, but could be used to cover an attackers
              tracks.

        - Change "number of invalid logins since last login" information
              Same as above.

        - Add/Remove restrictions on the max # of invalid login attempts
              Could allow a "brute force" technique to work on an
              account password if the restriction was lifted. Also, if
              an attacker set this restriction to 1 invalid login, that
              account would be disabled if a single failed login attempt
              was made. This would be very annoying to the SuperUser who
              would end up having to reset accounts fairly often.

        It is important to know however, that a renegade user can never
        grant himself SuperUser privileges, nor can he ever attempt to
        effectively modify a password. To perform any of these
        functions, he MUST be logged in as a SuperUser. In addition,
        NOBODY (not even SuperUsers) can view passwords.
        (They can never be decrypted, remember?)

        In essence:
        Sentry does it's part for security, but you must do yours as
        well...
                       GUARD YOUR SUPERUSER PASSWORDS!


        12.2 Hardware Loopholes

        Although it is unlikely that a user will do this, there is a
        potential security risk to Sentry. Fortunately, this method can
        only be implemented by highly technical users. If a user really
        wants to get into your system, he can disassemble it, and take
        the battery out of your BIOS. This will reset your BIOS to the
        standard setup, which does not include password protection. From
        there, the user can enter your BIOS, and change the boot
        sequence from C,A to A,C. This means that your computer will
        search for a boot disk before booting from your hard drive.
        Therefore, the user can get in if he has a pre-made boot disk.

        Like I said, it's unlikely, but possible. If you want to fix up
        this back door, you can re-wire your floppy disk drive so that
        it is never used on boot up. I do not have instructions for that
        at this time, however I am looking, and will include them in
        future.

        Along the same lines, a user could replace your hard drive (the
        one containing Sentry)  with another hard-drive. This way he
        could then boot up using the new hard drive, and never have to
        worry about Sentry. Also, if he kept your hard drive on the
        system (as drive D for example), he could still access your
        data. This kind of trickery is highly improbable, but not
        impossible.

        The above two methods take more technical skill than the average
        user possesses, and should not be considered a serious threat. I
        include them simply so you can be aware such things exist. If
        you are concerned about attacks of this nature, you should
        secure your system's case to the frame (IE: make it impossible
        to open the case with a screwdriver - install a locking
        mechanism or fuse the screws to the frame).

        It is critical to realize that it is EXTREMELY difficult to
        repel a determined and well-organized attack. Using Sentry does
        not guarantee your computer's safety. It does however greatly
        reduce the threat of a successful attack, and more importantly,
        it can alert you to potential threats before they become a
        serious problem. Your ability to defend is much greater once you
        know you are under attack. Sentry can keep you informed of
        suspicious actions on your PC, as well as being is a powerful
        tool in defeating most threats.


        13.0 Troubleshooting
        ====================

        13.1 Error messages

        Below are listed all possible error messages you can get while
        running Sentry. With each is a brief description of what it
        means, probable causes, and how to fix it.

        Please be aware that ALL of these errors cause Sentry to
        lock-up. This may be an inconvenience at times, but it is done
        for security reasons (that way an attacker can't "induce" an
        error and get into the system).

        13.1.1  Cannot locate environment.

        This indicates an error with your DOS environment. Make sure
        that you are using the regular environment, or that it is set up
        correctly.


        13.1.2  Environment overflow - not modified.

        There was an error trying to set modify the DOS environment. It
        may occur if you try to run Sentry from within the Sentry DOS
        shell (IE: running Sentry from Windows, then when you're in the
        shell, running it again). If this error occurs, you are
        generally using too many environment variables for the amount of
        space you have allotted. See your DOS manual for ways of
        increasing environment space.


        13.1.3  Error Creating Backup Log File!

        There is a problem with the backup log file. Make sure that the
        file pointed to by the initialization settings is not
        write-protected, hidden or a system file.


        13.1.4  Error Creating Log file!

        The file that logs all transactions to your computer cannot be
        created. Make sure you have specified a valid pathname for this
        setting, and make sure you have about 80k of free space on your
        drive. If a log file already exists, it will be appended to.
        Otherwise it will be created.


        13.1.5  Error Creating Temp file!

        Sentry cannot create a temporary file. Make sure you have at
        least 80k available on the hard drive that contains Sentry
        before running it.


        13.1.6  Error Opening Log File!

        There is a problem with the log file. Make sure that the log
        file pointed to by the initialization settings is not
        write-protected, hidden or a system file.


        13.1.7 Error Opening Message File!

        This error indicates that the message file cannot be opened.
        Ensure that your initialization setting for the message file is
        correct, and that the file is not read-only, hidden, or a system
        file.


        13.1.8 Error Opening Protected File!

        This error may occur when protecting a file from the SuperUser
        menu. Make sure the file you indicate to protect is readable.


        13.1.9 Error Opening Sentry.ins!

        This error occurs when Sentry cannot find the file containing
        the descriptions for the initialization settings. Make sure that
        the file Sentry.ins is in the same directory as the Sentry.exe
        file.


        13.1.10 Error Opening System Files!

        This is an error during installation. If this error occurs, make
        sure that your AUTOEXEC.BAT, CONFIG.SYS and MSDOS.SYS (Win 95
        users only) files are readable, if they exist.


        13.1.11  Error Opening Temp File!

        A temporary storage file cannot be opened. Make sure you have at
        around 80k of disk space left when you run Sentry.


        13.1.12  Error Reading Data Segment! [Open]

        This occurs when the initialization settings or account
        information is not acting as expected. Make sure that you have
        about 80k of disk space free, and that your Sentry.exe file is
        not read-only.


        13.1.13  Please Run the INSTALL.EXE Program.

        This usually indicates that there are no initialization
        settings. The easiest way to remedy this is to re-install Sentry
        (see section 2 for details). That will create initialization
        settings, or over-write the old settings if they are invalid.


        13.1.14  Error Scanning Temp File!

        This error should never occur. If it does, please contact me
        with details of the scenario.


        13.1.15  Error in Account Information!

        This means there is a problem with the account information for a
        certain user. You can either try restoring your sentry.exe file
        from backup, or you can re-install it (see section 2 for
        details). If you continue to use corrupt account information,
        you will find you are locked out quite frequently. It should be
        a top priority to fix the account info.


        13.1.16  Error in Initialization Settings!

        Your initialization settings are corrupt or could not be read.
        The best bet here is to re-install Sentry from scratch, and
        over-write the current settings. If you find this occurring
        frequently, it is probably a bug of some sort, and I should be
        contacted.


        13.1.17 Internal Screen Error. [Reading]

        This error should never occur. Having said that, if it does,
        your best bet is to check your video mode. Sentry has only been
        tested in 80x25 text mode, so make sure that is what you are
        using. If this error crops up, please contact me with the
        details.


        13.1.18 Internal Screen Error. [Writing]

        See above.


        13.1.19 Out of memory!

        When this error appears, it means that for some reason, Sentry
        didn't have enough memory to run. This is extremely rare, since
        Sentry requires very little memory. If this error occurs, try
        freeing up some memory by unloading some un-needed programs, or
        rebooting.


        13.1.20 Registration Error - Program Aborted!

        Someone (probably you) has tried unsuccessfully to change the
        registration information. Very naughty, but if you want to fix
        it, simply restore Sentry.exe from your backup copy. (Again, a
        good reason to keep a backup somewhere!)


        13.1.21 This account has expired.

        Sorry, you're out of luck. The SuperUser(s) have set your
        account to expire, and so it has. If you ARE the SuperUser,
        silly you (you shouldn't let your own account expire!). In that
        case, you will have to restore the Sentry.exe from a backup,
        and make the necessary changes to get your system running.


        13.1.22 Cannot Find LICENSE.TXT!

        The file LICENSE.TXT was not found by the install program. This
        file must be present for the install to proceed correctly. If
        you are missing this file, check section 11.3 for information on
        where to obtain it.


        13.2 Other problems

        When I run Sentry, is displays a warning saying I have
        newer/older initialization settings.

        A: You should probably get the latest version of Sentry (see
        section 11.3 for info on obtaining the latest version). Replace
        all your current files with the files you retrieve. This warning
        may not be a problem in itself, however it is not a good idea to
        use initialization settings from a different version.


        I get a warning about users being tampered with in the log file.

        A: Someone has been tampering with your users (obviously). They
        thought they could change the SuperUser access on your system,
        but really couldn't. The only side effect of this is that some
        users may appear to have SuperUser access when they don't (and
        vice-versa) when you view them from the SuperUser menu. The
        users' actual access has not changed. To remedy this situation,
        you can get the user to enter another password (this can easily
        be done by expiring their current password). As soon as the new
        password is entered, the problem will disappear.


        I can't log in at all.

        A: Are you a user on the system? Are your initialization
        settings set up correctly? Have you run the install program?


        I can't log in as a SuperUser.

        A: Did you give yourself SuperUser access? Are you remembering
        to hold down CTRL when you hit enter?


        My account information is corrupt or deleted.

        A: Pray you kept a backup somewhere. At the very least, you
        should have the install program sent with Sentry. In that case,
        re-install, and log in as Sentry. Since Sentry is initially a
        SuperUser, you can re-create your users (don't forget to delete
        the Sentry user when you are finished!).


        I can't create a c:\Sentry directory on my drive.

        A: If you are using MS-DOS's UNDELETE program, it may create a
        directory called "Sentry" off of your root directory. This
        directory is hidden, and can only be seen with the "dir /a"
        command. (This only occurs if you are using the "delete sentry"
        mode). Possible fixes are to stop using "delete sentry" mode, or
        to create your Sentry directory as something else (eg:
        c:\Sentry2, c:\Secur\Sentry, etc etc).


        14.0 Standard Disclaimer
        ========================

        Inexperienced users should take care with this program, as you
        may lock yourself out of your computer!

        If you feel you want to use it, but don't feel completely
        confident, leave a "back door" for you to use. (IE: don't
        implement all of the security measures listed in "Securing Your
        Computer"), so that if you DO get locked out, you can still get
        in somehow. Once you are satisfied that all is well, lock up the
        back door too.

        Please read the document "LICENSE.TXT" included with this
        software for the entire licensing agreement.


        15.0 Contact Information
        ========================

        I would greatly appreciate any comments you might have about
        this program (either positive or negative). If you encounter any
        problems, or have a suggestion for making Sentry better, please
        let me know, and I'll try to put it in a future release. I look
        forward to hearing from you.

        You can contact me via e-mail at Mike.Bobbitt@@AcadiaU.Ca and I
        will reply as quickly as I can. If you do not have internet
        access, you can contact me via surface mail at:

        NightShade Computing
        P.O. Box 1336
        Wolfville, Nova Scotia
        B0P 1X0
        CANADA


        16.0 Credits
        ============

        My thanks go out to these people:

        Mark Saarinen for the password encryption algorithm.

        Richard Brittain for use of his DOS environment variable code.

        D.J. Houghton and Rob Coombs for testing and advising during the
        design phase.

        Dexter J. Caldwell for suggestions on various options, as well
        as the "template" methodology  for protected files.

        L.D. Best for suggestions, comments and bug reports, as well as
        detailed explanations of test situations. L.D. has provided
        many good ideas and useful comments with respect to Sentry, and
        has assisted greatly in "fine tuning" many features such as file
        protection.

        Bret Jacobsen for finding some serious errors in the first
        release, as well as continually making suggestions for
        improvement. Bret has given invaluable assistance in the
        development of Sentry.


        ...And my wife for listening to me talk incessantly about it.
@


3.2
log
@Mini-mail system.
@
text
@d17 1
a17 1
                                    V3.2
d21 2
d25 2
a26 2
                          Mike.Bobbitt@@AcadiaU.Ca
               http//dragon.acadiau.ca/~910318b/Sentry.html
d30 1
d38 3
a40 1
                 1.1.2 In the Business Environment
d44 2
d49 1
a49 1
            2.1  General Setup Issues
d53 1
a53 1
            2.5  Modifying Your AUTOEXEC.BAT
d58 6
a63 4
            3.3  Switches in CONFIG.SYS
            3.4  Passwords
            3.5  Placement in AUTOEXEC.BAT
            3.6  Keep a Backup
d70 22
a91 12
            5.1  Create User
            5.2  Delete User
            5.3  View Users
            5.4  Toggle SuperUser Status
            5.5  Change Account Exipry Date
            5.6  Change Password Expiry Date
            5.7  View Log File
            5.8  Change Account Password
            5.9  Assign Max Invalid Logins
            5.10 Edit Initialization Settings
            5.11 Send a Message to a User
            5.12 Exit
d96 1
a96 2
            6.3  Additional Windows Security
            6.4  Windows 95
d101 3
d111 39
a149 18
        10.0 Revision History
             10.1  Pre-Release Notes
             10.2  Sentry V1.0
             10.3  Sentry V1.1
             10.4  Sentry V1.2
             10.5  Sentry V1.3
             10.6  Sentry V1.4
             10.7  Sentry V2.0
             10.8  Sentry V2.1
             10.9  Sentry V2.2
             10.10 Sentry V2.3
             10.11 Sentry V2.4
             10.12 Sentry V2.5
             10.13 Sentry V2.6
             10.14 Sentry V2.7
             10.15 Sentry V3.0
             10.16 Sentry V3.1
             10.17 Sentry V3.2
d159 2
a160 1
             11.8  General
d168 22
a189 14
                   13.1.1  Environment overflow - not modified.
                   13.1.2  Error Reading Data Segment! [Append]
                   13.1.3  Error Reading Data Segment! [Open]
                   13.1.4  Error Reading Data Segment! [Scan]
                   13.1.5  Error in Initialization Settings!
                   13.1.6  Error in creating log file!
                   13.1.7  Error in time stamps.
                   13.1.8  Error opening log file!
                   13.1.9  Error opening temp file!
                   13.1.10 Internal Screen Error. [Reading]
                   13.1.11 Internal Screen Error. [Writing]
                   13.1.12 Out of memory!
                   13.1.13 Registration Error - Program Aborted!
                   13.1.14 This account has expired.
d199 2
a200 1
 
d232 3
a234 3
        people off your PC. It is flexible enough that this single
        purpose can be used in many different ways, for many different
        reasons. Here are just a few.
a235 1

d241 1
a241 1
        possibly, you just want to keep track of who is using your
d250 1
a250 1
        1.1.2 In the Business Environment
d253 9
a261 9
        unauthorized entry into PC's. With Sentry, you can leave your
        terminals unattended while knowing that nobody can access the
        information held on them, unless you want them to. Many
        businesses have cleaners or other independent contractors come
        in during silent hours. A lot of businesses have PC's in open
        areas where a "passer-by" could use them. Most terminals are
        left unattended for a portion of the day (lunch, during errands,
        during meetings, etc.). There's no guarantee that an unauthorized
        person won't attempt to use your PC's when you're not around.
d270 16
d310 1
a310 1
        viewed by a SuperUser at any time.
d326 1
a326 4
        Sentry can be used to restrict access when you first turn on
        your PC, to block DOS access from within Windows, to secure a
        single program from general use, or any combination of the
        above.
d328 16
d345 1
d358 1
a358 1
        registered user).
d372 1
a372 1
        2.1 General Setup Issues
d378 31
a408 8
        From here, installation is painfully simple. Just run the
        program called INSTALL.EXE. This program will automatically
        search to see if your copy of Sentry already has initialization
        settings. If it does, you will be asked if you wish to
        over-write them. Enter 'y' if you wish to overwrite them. Any
        other input aborts the action. If you do not already have
        initialization settings, the install program will automatically
        use the defaults.
d412 2
a413 2
        access. Make sure you keep a backup of the install program in
        case you need it.
d418 28
a445 5
        Now the next thing you must do is to change the password and
        login provided with the initial copy of Sentry. To do this, you
        must run the Sentry.exe program. If it displays an error
        message, check the troubleshooting section at the end of this
        file.
d447 2
a448 19
        When it asks for a login, use "Sentry", with the password
        "Sentry". You can turn case sensitivity off via the
        initialization settings, but only for logins. The password must
        be entered exactly as shown (sentry or SENTRY will not work).
        The Sentry account has SuperUser access, meaning you can create
        and delete accounts while logged in as Sentry. To log in as a
        SuperUser, enter Sentry for a login, and instead of pressing
        enter, hold down the CONTROL key and press enter. This tells the
        Sentry program that you want to log in as a SuperUser. Then
        enter your password normally, and instead of dropping to DOS,
        you will go to the SuperUser menu. (See the section below on
        "The SuperUser Menu" for more information).

        From here, you should create a new user (you) and grant yourself
        SuperUser access. You can do this during creation by holding the
        CTRL key while pressing enter after typing your login name. You
        can also do this by using the "Create User" option normally and
        then using the "Toggle SuperUser Access" menu option to give
        yourself SuperUser privileges.
d478 23
a500 32
        Settings" option (see section 5.10). Each setting includes
        helpful hints and information to simplify customization. Any
        changes you make will not take effect until the next time you
        use Sentry.


        2.5 Modifying Your AUTOEXEC.BAT

        Simply add the following line to the top of your AUTOEXEC.BAT
        file:

        ----------------- CUT ----------------
        \Sentry\Sentry
        ----------------- CUT ----------------

        The above example assumes you have installed Sentry on
        c:\Sentry, which may not be true. Adjust the path in the first
        line to reflect the location of Sentry on your system.

        NOTE: These lines MUST be the first lines in your AUTOEXEC.BAT
        file. If not, the user may be given a chance to bypass Sentry by
        pressing CTRL-C or CTRL-BREAK.

        If Sentry is installed on a drive other than the one you boot
        from (drive D in the example below), then add these lines
        instead:

        ----------------- CUT ----------------
        d:
        \Sentry\Sentry
        c:
        ----------------- CUT ----------------
d519 2
a520 2
        main menu and set the SECURITY OPTION to setup (as opposed to
        system) in the BIOS FEATURES SETUP screen. Depending on the
d534 1
a534 1
        3.3 Switches in CONFIG.SYS
d536 2
d539 37
a575 4
        The /n will disallow pressing F8 to step through the CONFIG.SYS
        and AUTOEXEC.BAT files. This means that users cannot bypass
        Sentry by this method. The /f switch is optional, it simply
        speeds up your boot-up time (by about 2 seconds).
d577 2
a579 1
        3.4 Passwords
d581 2
d599 1
a599 1
        3.5 Placement in AUTOEXEC.BAT
d605 3
d609 1
a609 1
        3.6 Keep a Backup
d691 35
a725 1
        5.1 Create User
d730 1
a730 1
        status, type in the username and hold down the CONTROL key when
d737 2
a738 2
        saved in encoded form. The ESCAPE key will abort this operation
        at any time.
d745 1
a745 1
        5.2 Delete User
d754 1
a754 1
        delete. The ESCAPE key will abort this option at any time.
d757 1
a757 1
        5.3 View Users
d769 3
a771 3
        multiple pages of users. Arrows (- and ) will be present if
        there are additional pages above/below. The ESCAPE key will exit
        back to the main menu.
d774 1
a774 1
        5.4 Toggle SuperUser Status
d792 1
a792 1
        5.5 Change Account Expiry Date
d821 1
a821 1
        5.6 Change Password Expiry Date
d849 1
a849 26
        5.7 View Log File

        Every time a user logs in, a record is kept on disk. If you want
        to view that online record, select this option. The log file
        will be displayed, one screen at a time. Once the entire log
        file has been displayed, Sentry will ask you if you want to
        clear the log file. Any input other than 'y' will exit, leaving
        the log file in tact. If you answer with a 'y', Sentry will
        clear out the old entries. The log file itself will not consume
        much disk space, and so it should be left in tact for historical
        reasons. You may find it necessary to refer back to the log file
        to verify certain events. If disk space is a constraint, you can
        copy the log file onto a floppy disk for storage.

        You should always keep a close eye on the log file as this will
        often tell you when something is wrong on your system. All error
        messages are saved to the log file, so you can see if Sentry has
        run into any problems. Also, it records the current time, and
        the username of the user attempting to log in. This will help
        you to identify any potential attacks on your system. The log
        file is hidden by Sentry, but you should also place it somewhere
        safe so that users cannot tamper with it. You can set the
        location of the log file via the initialization settings.


        5.8 Change Account Password
d854 6
a859 6
        account, you should set the expiry date to be immediately, so the
        user is forced to choose a new one. If the previous password had
        no expiry date, none is assigned to the new password. Otherwise
        the password expires in the number of days assigned in the
        initialization settings. You can abort at any time by pressing
        the ESCAPE key.
d862 1
a862 1
        5.9 Assign Max Invalid Logins
d872 1
a872 1
        wish to change. Pressing the ESCAPE key will abort the operation
d911 74
a984 1
        5.10 Edit Initialization Settings
d986 6
d1019 2
d1022 1
a1022 1
        5.11 Send a Message to a User
d1025 1
a1025 1
        any user on the system (including themself). Once this option is
d1038 124
a1161 3
          The user then has the option to delete the message. If they do
          not delete the message, they will also see it on their next
          login.
a1162 3
          NOTE: Messages are displayed before any login information, so
          you can send messages to users that are locked out. That way,
          if you wish to send an explaination, you can.
d1164 1
a1165 2
        5.11 Exit

d1167 1
a1167 1
        pressing the ESCAPE key.
d1197 8
a1204 8
        Copy both of these files into your windows directory. Now, enter
        Windows and from the Program Manager, select [F]ile, then [N]ew.
        Next select Program Group. When prompted, enter "Sentry" for
        both description and file name. Now you should see a new program
        group called Sentry. The Sentry program group should contain a
        single icon, labeled MS-DOS. This icon actually points to
        sentry.pif, which contains specific information about running
        Sentry.
d1248 2
a1249 2
        Alternatively, you can add the security measures described in
        section 6.3 below.
d1251 10
a1260 16
        And that's it. If it seems like a complicated process, just try
        the steps one at a time, and make sure everything works ok. The
        end result is that when you click on the MS-DOS icon, it will
        run Sentry before dropping you to the DOS shell. That means that
        you can limit access to the operating system, without pulling
        any fancy tricks in Windows. Since you have made a new instance
        of Sentry, you could have one instance run when you boot up
        (giving access to windows), and have another instance run when
        you click on the DOS icon (giving access to the operating
        system). That way, a user that has access to your PC may not be
        able to drop to DOS.

        Be warned however that Sentry will still lock up your DOS
        session when a user fails to log in. This may cause you to lose
        any information you have not saved in your Windows session, if
        Windows becomes unstable.
d1262 2
a1263 1
        If Sentry does lock up your DOS session, you may be able to
d1269 1
a1269 36
        6.3 Additional Windows Security

        There are additional security measures built into Windows that
        should be considered when using Sentry. After all, securing the
        MS-DOS icon won't do any good if someone can edit it back to the
        way it was.

        To add more security to your Windows system, just add this
        Restriction section to your progman.ini file:

        ----------------- CUT ----------------
        [Restrictions]

        EditLevel=4
        rem Stops the creation, movement, copying, deletion, or
        rem modification of ANY groups or icons.

        Noclose=1
        rem Prevents a user from exiting windows.

        NoRun=1
        rem Disables the run command selection from the file menu.

        NoSave=1
        rem Stops the selection of save settings on exit from program
        rem manager.

        NoSaveSettings=1
        rem Disables the save settings on exit command, so any changes
        rem made to the your program manager group icons and windows
        rem cannot be saved upon exiting windows.
        ----------------- CUT ----------------

        To reverse any of these entries, remove it or change the value
        from to 0.  You can delete the file manager Icon as an additional
        security precaution.
a1270 3

        6.4 Windows 95

d1275 15
d1306 3
a1308 6
        program. It might be a word-processor, a mail program, or even
        Windows. In any case, you can secure it with Sentry, even if you
        don't use Sentry during boot-up. You will probably want to
        create a new instance of Sentry (see below) for each program you
        want to secure. That will allow you to have different accounts
        and passwords for each program.
d1313 46
a1358 5
        To set this up, all you have to do is write a batch file of the
        following format, and stick it in a directory in your path.
        (C:\DOS is almost always in your path, so you could stick these
        batch files there). In this example, we will secure the program
        called RUNME (located at C:\prog\runme.exe):
d1360 48
a1407 26
        ----------BEGIN RUNME.BAT-----------------
        @@echo off
        c:
        \Sentry\Inst2\Sentry
        cd \prog
        runme
        cd \
        -----------END RUNME.BAT------------------

        The program as shown above will run Sentry before it runs
        RUNME.EXE. As long at the batch file is in your path ahead of
        RUNME.EXE, RUNME.BAT will execute first, barring the user from
        running RUNME.EXE without running Sentry first. C:\DOS is almost
        always first in your path, so this will work for everything but
        DOS programs. You can add a new directory to you path by editing
        your AUTOEXEC.BAT. If you add it to the beginning, and place all
        your batch files there, they will run first. The only exception
        to this rule is that if the user is in the directory containing
        RUNME.EXE they will not execute RUNME.BAT first.

        This is not by any means a perfect method of securing a program.
        It will work in most cases, but with the proper knowledge and
        patience, this method can be defeated. If your users are
        skilled, don't rely on this method to be "bullet-proof." (Sentry
        was not designed for this purpose, it is merely an additional
        use).
d1409 2
a1410 2
        Future versions of Sentry may have an "automated" method for
        doing this if the need exists.
d1456 5
a1460 3
        If you use Sentry on your machine(s), I urge you to register. I
        have put a lot of time and effort into making Sentry a viable
        security program, and I would appreciate the effort very much.
d1475 1
a1475 1
        serious about Security, plaintext passwords are not a viable
d1494 2
a1495 1
              - Free upgrades as soon as they are available.
d1514 43
a1556 2
        10.0 Revision History
        =====================
d1558 1
a1558 1
        10.1 Pre-Release Notes
d1560 1
a1560 3
        March 95   - My search for DOS security programs is
                     unsuccessful. The general idea for Sentry is
                     formed.
d1562 4
a1565 1
        April 95   - Coding for Sentry begins.
d1567 1
a1567 1
        May 95     - Still coding...
a1568 1
        June 95    - Sentry is now a complete program.
d1570 1
a1570 1
        July 95    - Beta testing. Many updates made.
d1572 1
d1574 1
a1574 1
        10.2 Sentry V1.0
a1575 1
        Release Date: 20 July 95
d1577 1
a1577 3
        - Sentry V1.0 (Shareware) is released. Contains basic
          functionality. At this point, Sentry is approximately 1700
          lines of code.
d1579 2
d1582 6
a1587 1
        10.3 Sentry V1.1
d1589 1
a1589 1
        Release Date: 27 July 95
a1590 2
        - Sentry V1.1 Released. V1.1 fixes some serious bugs in V1.0,
          and has these additions:
d1592 1
a1592 1
          * Date format is selectable.
d1594 2
a1595 2
          * Users with no password expiration are not assigned an expiry
            date on entering a new password.
d1597 4
a1600 2
          * Incorrect password verification displayed immediately when
            creating a new user, or toggling SuperUser status.
d1602 1
a1603 1
        10.4 Sentry V1.2
d1605 1
a1605 1
        Release Date: 29 July 95
d1607 4
a1610 2
        - Sentry V1.2 Released. Some more minor bugs are repaired and
          several areas are updated. Additions are:
d1612 1
a1612 1
          * Memory management improved.
a1613 1
          * All user stats now shown instead of just login name.
d1615 1
a1615 2
          * The keyboard buffer is flushed after an invalid login
            attempt.
d1617 1
d1619 1
a1619 1
        10.5 Sentry V1.3
a1620 1
        Release Date: 01 Aug 95
d1622 1
a1622 2
        - Sentry V1.3 Released. Again, more bugs were fixed in this
          version. Additions are:
d1624 2
a1625 2
          * The log file is now much more detailed than before, and
            includes a time stamp on every action.
d1627 2
a1628 4
          * A bug with deleting a user listed as 15th or later in the
            password file has been fixed. (Regardless of what page the
            user you selected to delete was on, a user from the first
            page was always deleted).
d1630 1
a1630 2
          * A bug in the multi-user display was fixed. (If the last page
            contained one user, you could not page down to see him).
d1633 1
a1633 1
        10.6 Sentry V1.4
d1635 3
a1637 1
        Release Date: 08 Aug 95
d1639 5
a1643 2
        - Sentry V1.4 Released. Some minor changes have been made,
          mostly for the sake of appearance. Additions are:
d1645 1
a1645 2
          * The Sentry.ini file now allows the user to select the
            colours to be used for normal and highlighted text.
d1647 1
a1647 3
          * Input routines have been improved and simplified.
            Inappropriate characters have been stripped from the input
            stream.
d1650 1
a1650 1
        10.7 Sentry V2.0
d1652 4
a1655 1
        Release Date: 11 Aug 95
d1657 5
a1661 3
        - Sentry V2.0 Released. Many revisions, fixes and additions have
          been made to the program for this release. Most of the update
          ideas came from Bret Jacobsen. Additions include:
d1663 1
a1663 2
          * Invalid login/password length messages (both to the screen
            and log file) are user-definable in the Sentry.ini file.
d1665 1
a1665 2
          * If a normal user attempts to log in as a SuperUser, it is
            recorded in the log file.
a1666 5
          * The SuperUser Login flag is cleared after an invalid login.
            (This is a bug fix: previously if CTRL-ENTER was pressed
            during an invalid login attempt, the next successful login
            attempt would be as a SuperUser, as long as the user had
            access).
d1668 1
a1668 2
          * A bug with the Toggle SuperUser Access option corrupting the
            time stamps has been fixed.
d1670 2
a1671 1
          * The log file is again re-organized to be more "readable."
d1673 1
a1673 4
          * You can no longer delete the last SuperUser on your system
            (thereby locking yourself out). Sentry performs a check
            previous to deletion and will abort if you are deleting the
            last SuperUser.
a1674 1
          * A bug with the input skipping characters was fixed.
d1676 1
a1676 2
          * After a successful login, the number of invalid login
            attempts since your last successful login is now shown.
d1678 2
a1679 2
          * The user can now abort a password change, unless the
            password has expired.
d1681 1
a1681 2
          * The option to reset an account's password has been added to
            the SuperUser menu.
a1682 4
          * You can now define the number of invalid logins permissible
            before an account expires (locks up). The default setting is
            defined in the Sentry.ini file, and the settings for
            individual accounts can be modified from the SuperUser menu.
d1684 1
d1686 3
a1688 1
        10.8 Sentry V2.1
d1690 1
a1690 1
        Release Date: 20 Aug 95
a1691 1
        - Modifications include:
d1693 1
a1693 5
          * Input no longer automatically ends after "MaxPasswordLen"
            characters have been entered at the login or password
            prompts. Input continues as required, however only
            "MaxPasswordLen" characters are used. Any extra characters
            are discarded.
d1695 3
a1697 3
          * Case sensitivity for logins can now be turned on and off via
            the Sentry.ini file. This is applicable to logins only,
            passwords are still case sensitive.
d1699 1
a1700 1
        10.9 Sentry V2.2
d1702 1
a1702 1
        Release Date: 10 Sep 95
d1704 2
a1705 1
        - Modifications include:
d1707 6
a1712 2
          * Sentry now uses windowed screens for all output, as opposed
            to simply directing output to the entire screen.
d1714 1
a1714 4
          * When entering dates, the year is now checked. If it is not 4
            characters, the user is forced to re-enter it. This was
            causing problems with Sentry accepting '96' as a valid year,
            and subsequently not translating correctly.
a1715 8
          * A bug with the password encoding scheme has been fixed. The
            encryption used to truncate passwords at length 8, causing
            only the first 8 characters to be recognized. For
            SuperUsers, this meant that passwords over 8 would not
            contain the SuperUser stamp (it was truncated). This problem
            has now been rectified, and passwords are significant for
            MaxPasswordLen characters. All in all, this seriously
            increases the amount of security available from Sentry.
d1717 1
a1717 4
            NOTE: Because of the above modification, older versions of
            Sentry cannot use password files from V2.2 and up. The
            reverse is not true however, as Sentry V2.2 can use password
            files all the way back to V1.0.
d1719 2
a1720 4
            Also note that to use passwords over 8 characters, you must
            re-create the old passwords. This can be easily done by
            selecting the "Change Account Password" option from the
            SuperUser menu.
d1722 6
d1729 1
a1729 1
        10.10 Sentry V2.3
a1730 1
        Release Date: 24 Sep 95
d1732 1
a1732 1
        - Modifications include:
d1734 2
a1735 1
          * Small bugs with windowed mode have been fixed.
d1737 6
a1742 2
          * Windowed mode is now optional. For those that prefer
            "normal" operation, you can set that in the Sentry.ini file.
d1744 1
a1744 2
          * Log file viewing can now handle long lines, and you can skip
            to the end of the file by pressing the ESC key once.
a1745 2
          * Quickstart instructions are now included in the Qstart.txt
            file.
d1747 1
d1749 2
a1750 1
        10.11 Sentry V2.4
d1752 6
a1757 1
        Release Date: 06 Oct 95
d1759 1
a1759 1
        - Modifications include:
a1760 5
          * The Sentry.ini file can now be edited from the SuperUser
            menu. The user can get information on each attribute,
            including a brief description, security notes, default
            setting, and the current setting just by selecting which
            attribute they wish to change.
d1762 1
d1764 2
a1765 1
        10.12 Sentry V2.5
d1767 1
a1767 1
        Release Date: 10 Oct 95
a1768 1
        - Modifications include:
d1770 1
a1770 3
          * Sentry can now be run from any location. The user does not
            have to be in the Sentry home directory for it to work
            properly.
d1772 2
d1775 3
a1777 1
        10.13 Sentry V2.6
d1779 1
a1779 1
        Release Date: 25 Oct 95
a1780 1
        - Modifications include:
d1782 1
a1782 4
          * The SuperUser may modify the "Login:" and "Password:"
            prompts to suit their custom environment. These are changed
            either through the Sentry.ini file or via the SuperUser
            menu.
d1784 2
a1785 4
          * Any setting changes made via the SuperUser menu are now
            recorded in the log file. This will help SuperUser keep a
            history of setting changes, which is useful in the case of a
            security audit.
d1787 1
a1787 8
          * An environment variable is now set by Sentry upon successful
            login. The variable is set to the username of the person
            logging in. This can be very useful if you wish other
            programs to link with Sentry and perform specific actions
            depending on who is logging in. (For example: if it is a
            SuperUser logging in, you may wish to display some system
            stats, or you may want to display individual greetings (or
            warnings) based on who is logging in).
d1790 1
a1790 1
        10.14 Sentry V2.7
d1792 2
a1793 1
        Release Date: 28 Oct 95
d1795 1
a1795 1
        - Modifications include:
a1796 4
          * Sentry now uses a screen saver to blank the screen during
            idle periods. Although this feature does not add to Sentry's
            security, it now means that users can run Sentry before
            leaving their terminal and not worry about burn-in.
d1798 1
d1800 2
a1801 1
        10.15 Sentry V3.0
d1803 3
a1805 1
        Release Date: 10 Nov 95
d1807 1
a1807 1
        - Modifications include:
a1808 4
          * The old password and Sentry.ini files are no more!
            These files have been done away with, since they posed a
            slight security risk. This removes the need to edit the
            initialization settings by hand.
d1810 1
a1810 4
          * You can no longer revoke SuperUser access from the last
            SuperUser on your system. By doing this, you could
            potentially lock yourself out of your system, so it is not a
            valid option any more.
d1812 4
a1815 3
          * "Exploding Windows" are now available. These can be turned
            on via the initialization settings. This is for appearance
            only, and has no effect on functionality.
d1817 1
a1817 4
          * The user can now select a message to appear randomly on the
            screen during the screen saver. This fixes a bug in previous
            versions where the cursor remained in the upper left corner
            during the screen saver, which could case burn-in.
d1819 1
a1819 3
          * Upon exiting the SuperUser menu, the screen is restored to
            the way it was before Sentry was run. This eliminates the
            problem of sensitive information remaining on your screen.
d1822 1
a1822 1
        10.16 Sentry V3.1
d1824 6
a1829 1
        Release Date: 03 Dec 95
d1831 1
a1831 1
        - Modifications include:
d1833 1
a1833 3
          * The user can now select the character to be echoed to the
            screen when a password is entered. In addition, the user can
            chose to have no character or the actual character echoed.
a1834 2
          * The log file now records when the Sentry DOS shell is
            entered and exited.
d1836 1
d1838 3
a1840 1
        10.17 Sentry V3.2
d1842 1
a1842 1
        Release Date: 08 Dec 95
d1844 1
a1844 1
        - Modifications include:
a1845 2
          * The maxixum number of invalid logins can now be set during
            user creation.
d1847 1
a1847 3
          * The initialization settings contain a parameter for
            automatically expiring accounts that have been inactive for
            a given amount of time.
d1849 4
a1852 3
          * SuperUsers can now send a one-line memo to any user
            (including themself). This is useful for reminders,
            warnings, or explainations (why is user X locked out?).
d1854 1
d1856 126
d1985 1
a1985 1
        11.1 Encoding Algorithm
d1987 1
a1987 1
        The encoding algorithm used is the standard UNIX crypt()
d2020 2
a2021 1
        11.2 SuperUser Access
d2052 1
a2052 1
        11.3 Files
d2059 4
d2065 2
a2066 2
        Order.frm       The order form.
        Qstart.txt      Quickstart instructions.
a2068 1
        License.txt     The license agreement.
d2079 1
a2079 1
        11.4 File_id.diz
d2090 8
a2097 8
        (V3.2) Sentry - Security for DOS/Windows.
        Sentry is a highly customizable security
        program that allows you to control and
        monitor access to your PC. It supports up to
        100 users with normal and "SuperUser" access.
        It can be used in Windows to secure the DOS
        icon. Used correctly, Sentry is an extremely
        powerful security tool for your PC.
d2103 1
a2103 1
        11.5 Time / Date
d2107 1
a2107 1
        month of 1997). This is obviously incorrect. I have determined
d2113 1
a2113 1
        This problem is under investigation.
d2116 1
a2116 1
        11.6 Environment Variables
d2132 1
a2132 2
        \sentry\sentry
        cls
d2134 3
a2136 1
        if %user==ROBERT goto robert
d2140 1
a2140 1
        :robert
d2142 1
a2142 1
        echo SuperUser (Robert) logged in.
d2144 1
d2149 1
a2149 1
        rem *** add more users as you see fit
d2151 2
a2173 1
        11.7 Virus Scanners
d2175 2
d2194 1
a2194 1
        11.8 General
d2196 31
a2226 4
        Sentry is written entirely in Borland C for DOS. As of version
        3.2, Sentry contains over 4200 lines of code. Portability
        between machines is not an issue, since Sentry has been designed
        and tested on standard MS-DOS machines.
d2253 2
a2254 2
        If a user did manage to decipher the account information, he
        could do any of the following:
d2271 3
a2273 3
              password to something usable. An edited password will
              likely lock that user out of their account, until the
              password is reset.
d2282 1
a2282 1
        - Add/Remove restrictions on the number of invalid login attempts
d2287 2
a2288 1
              was made.
d2363 1
a2363 1
        13.1.1  Environment overflow - not modified.
d2365 3
a2367 4
        There was an error trying to set modify the DOS environment. If
        this error occurs, you are generally using too many environment
        variables for the amount of space you have allotted. See your
        DOS manual for ways of increasing environment space.
d2370 1
a2370 1
        13.1.2  Error Reading Data Segment! [Append]
d2372 7
a2378 3
        This error only occurs during user creation. If you encounter
        this error, make sure that your Sentry.exe file is not
        read-only.
d2381 1
a2381 1
        13.1.3  Error Reading Data Segment! [Open]
d2383 3
a2385 6
        This occurs when the initialization settings or account
        information is not acting as expected. Make sure that you have
        about 80k of disk space free, and that your Sentry.exe file is
        not read-only.

        13.1.4  Error Reading Data Segment! [Scan]
a2386 13
        This usually indicates that there are no initialization
        settings. The easiest way to remedy this is to re-install Sentry
        (see section 2 for details). That will create initialization
        settings, or over-write the old settings if they are invalid.


        13.1.5  Error in Initialization Settings!

        Your initialization settings are corrupt or could not be read.
        The best bet here is to re-install Sentry from scratch, and
        over-write the current settings. If you find this occurring
        frequently, it is probably a bug of some sort, and I should be
        contacted.
d2388 1
a2389 2
        13.1.6  Error in creating log file!

d2397 1
a2397 1
        13.1.7  Error in time stamps.
d2399 3
a2401 6
        This means there is a problem with the time stamps on a user's
        account. You can either try restoring your sentry.exe file from
        backup, or you can re-install it (see section 2 for details). If
        you continue to use corrupt account information, you will
        find you are locked out quite frequently. It should be a top
        priority to fix the account info.
d2404 1
a2404 1
        13.1.8  Error opening log file!
d2408 23
a2430 1
        write-protected.
d2433 1
a2433 1
        13.1.9 Error opening temp file!
d2435 7
d2446 33
a2478 1
        13.1.10 Internal Screen Error. [Reading]
d2480 9
d2496 1
a2496 1
        13.1.11 Internal Screen Error. [Writing]
d2501 1
a2501 1
        13.1.12 Out of memory!
d2510 1
a2510 1
        13.1.13 Registration Error - Program Aborted!
d2518 1
a2518 1
        13.1.14 This account has expired.
d2527 8
d2562 2
a2563 3
        A: Make sure you are a user on the system. Make sure your
        initialization settings have been set up correctly. Have you run
        the install program?
d2583 1
a2583 1
        A: If you are using MS-DOS's Undelete program, it may create a
d2608 1
d2613 1
a2613 1
        this program (either positive or negative). If you find any
d2622 1
a2622 1
        Michael A. Bobbitt
d2624 1
a2624 1
        Wolfville, NS
d2634 1
a2634 1
        Mark Saarinen for the encryption algorithm.
d2641 9
d2654 1
@


3.1
log
@Password echo char & log DOS shell.
@
text
@d17 1
a17 1
                                    V3.1
d71 2
a72 1
            5.11 Exit
d107 1
d502 12
a513 7
        After correctly entering your password, the date and time of
        your last login will be displayed. If there have been any
        invalid login attempts made against your account since the last
        valid login, you will be told so, and how many. If the number of
        invalid login attempts against your account has exceeded the
        maximum allowed, your account will be locked out until the
        SuperUser resets it.
d790 25
d1444 18
d1566 1
a1566 1
        (V3.1) Sentry - Security for DOS/Windows.
d1572 2
a1573 2
        icon. Installed correctly, Sentry is an
        extremely powerful security tool for your PC.
d1668 1
a1668 1
        3.1, Sentry contains over 3700 lines of code. Portability
@


3.0
log
@Readme File for Sentry V3.0
@
text
@d17 1
a17 1
                                    V3.0
d24 1
a24 1
               http://dragon.acadiau.ca/~910318b/Sentry.html
d27 1
d105 1
d141 3
a143 1
        15.0 Credits
d146 2
a147 1

d203 1
a203 1
        businesses have cleaners or other independant contractors come
d207 2
a208 2
        during meetings, etc). There's no guarantee that an unauthorized
        person won't attempt to use your PC's when your're not around.
d269 1
a269 1
        SentryXX.zip file you initially recieved is the only format that
d385 1
a385 1
        NOTE: These lines MUST be the first lines in your autoexec.bat
d434 1
a434 1
        The /n will dis-allow pressing F8 to step through the CONFIG.SYS
d586 1
a586 1
        multiple pages of users. Arrows ( and ) will be present if
d696 1
a696 1
        account, you should set the expiry date to be immediatly, so the
d738 1
a738 1
        account it set the the day it was locked out.
d796 1
a796 1
        immediatly upon startup (I.E.: your autoexec.bat contains "win"
d821 1
a821 1
        single icon, labelled MS-DOS. This icon actually points to
d842 1
a842 1
        shoould take you directly to Sentry. Once you have entered a
d854 1
a854 1
        autoexec.bat file is running windows on startup, you can block
d857 1
a857 1
        your autoexec.bat.
d859 1
a859 1
        For example, the last lines of your autoexec.bat might look like
d927 2
a928 2
        from to 0.  You can delete the file manager Icon as an additonal
        security precation.
d967 1
a967 1
        called RUNME (loacted at C:\prog\runme.exe):
d1005 1
a1005 1
        new copy of Sentry, that works independantly of all other
d1022 1
a1022 1
        organized, and seperate from your other programs. Create a
d1030 1
a1030 1
        instance is independant of the others. Your account information
d1087 1
a1087 1
              - A clear concience knowing that you paid for your
d1092 1
a1092 1
        Y's. The version of Sentry that you recieve is good only for you
d1186 1
a1186 1
            Inapropriate characters have been stripped from the input
d1398 14
d1464 1
a1464 1
        crypt(super(password))        <-- Encoded password password with
d1494 1
d1516 1
a1516 1
        (V3.0) Sentry - Security for DOS/Windows.
d1589 1
a1589 1
        ** NOTE: Altough the environment variables are secure
d1618 1
a1618 1
        3.0, Sentry contains over 3700 lines of code. Portability
d1631 1
a1631 1
        be expoited. Because of this, I am listing below all of the
d1637 1
a1637 1
        With the releaase of Sentry V3.0, account information has become
d1647 1
a1647 1
        If a user did manage to decypher the account information, he
d1724 1
a1724 1
        user posesses, and should not be considered a serious threat. I
d1733 1
a1733 1
        not guarentee your computer's safety. It does however greatly
d1773 1
a1773 1
        This occurrs when the initialization settings or account
d1817 1
a1817 1
        file pointed to by the initialization settigns is not
d1938 5
a1942 2
        I take no responsibility for how you use this program, or any
        effects it may have on your system.
d1944 5
a1948 5
        Having said that, I would greatly appreciate any comments you
        might have about my program (either positive or negative). If
        you find any problems, or have a suggestion for making Sentry
        better, please let me know, and I'll try to put it in a future
        release. I look forward to hearing from you.
d1958 1
d1961 1
a1961 1
        15.0 Credits
@


2.7
log
@Readme file for Sentry V2.7.
@
text
@d17 1
a17 1
                                    V2.7
d44 1
a44 1
            2.4  Using the Sentry.ini file
d52 2
a53 3
            3.5  The Password File
            3.6  Placement in AUTOEXEC.BAT
            3.7  Keep a Backup
d103 1
d112 2
a113 1
             11.7  General
d116 1
a116 1
             12.1  The Password File
d121 14
a134 11
                   13.1.1  Error opening password file!
                   13.1.2  Error opening temp file!
                   13.1.3  Error in creating log file!
                   13.1.4  Error opening log file!
                   13.1.5  Error opening Sentry.ini file!
                   13.1.6  Error in Sentry.ini file! [XXXXXXXX]
                   13.1.7  Registration Error - Program Aborted!
                   13.1.8  Error in time stamps.
                   13.1.9  Out of memory!
                   13.1.10 This account has expired.
                   13.1.11 Internal Screen Error. [Reading|Writing]
d160 4
a163 4
        avoid potential problems. But what of the single-user PC? Is the
        information contained on these any less valuable? Often times
        not, yet adequate security programs do not exist for PC's. In my
        search for security, I discovered that PC's were virtually
d177 1
d180 6
a185 6
        Most people have something on their home PC that they don't want
        others to see. Maybe it's a sensitive document, maybe it's
        copies of e-mail, or maybe you just want to keep track of who is
        using your system. Sentry has the solution for all of these
        problems, by restricting access and logging all attempts to use
        the system.
d200 4
a203 3
        areas where a "passer-by" could use them. There's no guarantee
        that these people won't attempt to use your PC's when your're
        not around.
d263 3
a265 3
        of the original files (and no others). Essentially, the .zip
        file you initially recieved is the only format that Sentry is
        distributable in.
d290 13
a302 7
        The second thing you have to do is to set up the Sentry.ini file
        for your system. You should load the file into a text editor
        (like MS-DOS's edit) and make the changes from there. There are
        instructions and tips provided for each item. Make sure you read
        and understand these instructions before making any changes, as
        an improperly set up Sentry.ini file can cause errors and
        security loopholes.
d314 11
a324 11
        "Sentry". You can turn case sensitivity off in the Sentry.ini
        file, but for logins only. The password must be entered exactly
        as shown (sentry or SENTRY will not work). The Sentry account
        has SuperUser access, meaning you can create and delete accounts
        while logged in as Sentry. To log in as a SuperUser, enter
        Sentry for a login, and instead of pressing enter, hold down the
        CONTROL key and press enter. This tells the Sentry program that
        you want to log in as a SuperUser. Then enter your password
        normally, and instead of dropping to DOS, you will go to the
        SuperUser menu. (See the section below on "The SuperUser Menu"
        for more information).
d352 1
a352 1
        2.4 Using the Sentry.ini file
d354 9
a362 16
        Sentry can be configured to your needs by way of the Sentry.ini
        file. This file contains information that you may wish to
        change, allowing Sentry to adapt to many different situations.

        The Sentry.ini file follows a very specific format, and if you
        deviate from it, Sentry will not work! Comments are allowed, as
        long as the comment line begins with a * character. Blank lines
        are also permitted. The order of the items in the Sentry.ini
        file is critical. Do not move items around. The comments
        provided with the Sentry.ini file will guide you through this
        stage. Feel free to add your own comment lines as you see fit.

        If this is too much for you, then you can edit the Sentry.ini
        file from the SuperUser menu. You can do this by selecting the
        "Edit Initialization Settings" option (see section 5.10). Many
        people find this easier than editing the actual file. Any
d453 1
a453 17
        3.5 The Password File

        Put your password file in a safe place. Although passwords are
        encoded, usernames and time stamps are not. Also remember, the
        encoding scheme is one way only, so if I encode login names, you
        will never be able to view who is in your password file (IE: you
        would have to "guess" which person to delete). Users can change
        time stamps in the password file, and this can cause serious
        problems, so KEEP IT SAFE!

        NOTE: Sentry automatically hides your password file for you.
        After you have run Sentry once, your password file (and log
        file) will not appear in directory listings. This will help your
        security, but is not a fool-proof method.


        3.6 Placement in AUTOEXEC.BAT
d460 1
a460 1
        3.7 Keep a Backup
d462 5
a466 3
        Keep a backup copy of all your Sentry files! Especially your
        password file! If something happens to these files, you may be
        locked out your computer if you don't have a backup.
d483 3
a485 3
        while pressing enter. If you do not have SuperUser access, or do
        not wish to log in as such, simply press enter. In either case,
        this will send you to the password prompt.
d489 1
a489 2
        not echoed to the screen. At this time, the date and time of
        your last login will be displayed.
d492 2
a493 2
        are set by the "MinPasswordLen" and "MaxPasswordLen" attributes
        in the Sentry.ini file respectively.
d495 7
a501 5
        If there have been any invalid login attempts made against your
        account since the last valid login, you will be told so, and how
        many. If the number of invalid login attempts against your
        account has exceeded the maximum allowed, your account will be
        locked out until the SuperUser resets it.
d507 4
a510 4
        corresponds to the length limits set out in the Sentry.ini file.
        Once you have entered and verified your new password, it is
        given a new expiry date according to the "PasswordExpiresIn"
        value in the Sentry.ini file.
d522 8
a529 8
        Sentry.ini file, and is displayed when Sentry starts up. To
        change your password, simply enter your user name as usual, and
        when prompted for your password, enter the pass key. You will
        then be prompted for your old  password (to make sure it is
        really you), and then you will be asked for your new password,
        which will be verified and saved to disk. Your new password will
        expire in the number of days designated by "PasswordExpiresIn"
        in the Sentry.ini file.
d543 8
a550 9
        pressing enter. Otherwise, just press enter when you're finished
        at the login prompt. Once that is complete, Sentry asks for the
        password. The password is not echoed to the screen. The user
        should choose and enter their own password. SuperUsers need not
        know what the passwords are since they can still manage the
        accounts without knowing them. The password is entered twice to
        ensure no typos were made, and then saved to the password file
        in encoded form. The ESCAPE key will abort this operation at any
        time.
d582 2
a583 2
        there are additional pages above and/or below. The ESCAPE key
        will exit back to the main menu.
d640 5
a644 6
        of days set in the "PasswordExpiresIn" option in the Sentry.ini
        file. Once a password has expired, the user cannot re-enter it.
        He must select a new password. (NOTE: Sentry does not keep
        historical records on passwords, so a user may alternate back
        and forth between 2 passwords. This is not a secure practice and
        should be avoided).
d669 5
a673 3
        clear out the old entries. This should be done fairly
        frequently, depending on how busy your system is. Large log
        files take up more disk space.
d683 1
a683 1
        location of the log file with the Sentry.ini file.
d694 3
a696 3
        the password expires in the number of days assigned to
        "PasswordExpiresIn" in the Sentry.ini file. You can abort at any
        time by pressing the ESCAPE key.
d703 2
a704 2
        defined in the Sentry.ini file ("InvalidLogins") and is assigned
        to all accounts when they are first used.
d750 7
a756 5
        This option allows you to edit the Sentry.ini file from within
        Sentry. Once this option is selected, all of the attributes from
        the Sentry.ini file are displayed. Simply select the attribute
        you wish to modify, and you will be given the following
        information:
a759 4
                - The name of the attribute as it appears in the
                  Sentry.ini file. This will appear in brackets under
                  the one-line description.

d775 1
a775 3
        will not save an invalid value. For this reason, you should
        change your Sentry.ini settings from the SuperUser menu whenever
        possible.
d854 2
a855 2
        For example, the last few lines of your autoexec.bat might look
        like this:
d874 1
a874 1
        system). That way, a user that has access to windows may not be
d877 3
a879 3
        Be warned however that Sentry will still lock up your system
        when a user fails to log in. This may cause you to lose any
        information you have not saved in your Windows session, if
d882 4
a885 4
        If Sentry does lock up your system, you may be able to recover
        back to Windows by pressing CTRL-ALT-DELETE and closing the DOS
        prompt. This will still not allow access to DOS, but you will
        not lose anything you were working on.
d921 3
a923 3
        To nulify any of these entries, remove it or change the value
        from 1 to 0.  You can delete the file manager Icon as an
        additonal security precation.
d1020 1
d1025 3
a1027 8
        instance is independant of the others. Your password file should
        not be the same for any 2 instances (otherwise there is no
        advantage to having 2 instances). That means that the PassFile
        setting in each Sentry.ini must be different, and your password
        files must be in different locations. For simplicity's sake, you
        may want to keep your password file for each instance in the
        same directory as the other related Sentry files. (The password
        file for Instance 1 goes into c:\Sentry\Inst1, and so on).
d1086 5
a1090 5
        user X's password file is encrypted differently than user Y's
        password file. The version of Sentry that you recieve is good
        only for you and your files. (Likewise, nobody else can use
        their copy of Sentry with your password file). See the order
        form for information on obtaining compatible versions of Sentry.
d1236 1
a1236 1
        - Sentry V2.1 Released. Changes include:
d1253 1
a1253 1
        - Sentry V2.2 Released. Changes include:
d1287 1
a1287 1
        - Sentry V2.3 Released. Changes include:
d1305 1
a1305 1
        - Sentry V2.4 Released. Changes include:
d1318 1
a1318 1
        - Sentry V2.5 Released. Changes include:
d1329 1
a1329 1
        - Sentry V2.6 Released. Changes include:
d1355 1
a1355 1
        - Sentry V2.7 Released. Changes include:
d1363 30
d1467 1
a1467 4
        Sentry.ini      The initialization file.
        Sentry.pwd      The password file.
        Sentry.pif      The Sentry .pif file for Windows.
        Sentry.grp      The Sentry Group file for Windows.
a1468 1
        Order.frm       The order form.
d1471 1
d1473 2
d1478 3
a1480 3
        If you do not have all of these files, Sentry will probably not
        work for you. You can pick up a complete copy of Sentry (and
        updates as they become available) at:
d1496 1
a1496 1
        (V2.7) Sentry - Security for DOS/Windows.
d1541 1
a1541 1
        if %user==SENTRY goto sentry
d1545 1
a1545 1
        :sentry
d1547 1
a1547 1
        echo SuperUser logged in.
d1553 1
d1576 18
d1595 1
a1595 1
        11.7 General
d1598 1
a1598 1
        2.7, Sentry contains over 3150 lines of code. Portability
d1615 1
a1615 1
        12.1 The Password File
d1617 9
a1625 10
        Let me once again stress again that the time stamps and user
        names are not encoded in the password file. This means that if a
        malicious user found the password file, and could edit it, he
        could wreak havoc on your system. Bear in mind that the password
        file is automatically hidden by Sentry, so finding it is not
        always easy. Also, most of these methods require a working
        knowledge of how Sentry operates, and that is not commonly
        available. The best source for that information would be from
        this file, which is deliberately missing some key pieces of
        "technical" information.
d1627 2
a1628 2
        If a user did manage to find the password file however, he could
        do any of the following:
d1633 2
a1634 2
              notified that their password has expired. An attacker
              cannot expire a password and then log in to that account.
d1673 1
a1674 2
                    KEEP YOUR PASSWORD FILE SOMEWHERE SAFE, AND
                    GUARD YOUR SUPERUSER PASSWORDS!
a1675 1

d1680 3
a1682 3
        only be implemented by technical users. If a user really wants
        to get into your system, he can disassemble it, and take the
        battery out of your BIOS. This will reset your BIOS to the
d1688 1
d1708 2
a1709 1
        to open the case with a screwdriver).
d1717 2
a1718 2
        know you are under attack. Sentry can assist in keeping you
        informed of suspicious actions on your PC, and it is a powerful
d1736 7
d1744 1
a1744 1
        13.1.1 Error opening password file!
d1746 3
a1748 4
        This means your password file cannot be found or opened. Make
        sure your password file is at the location specified by
        "PassFile" in your Sentry.ini file. As long as it's there, you
        should have no problems.
d1751 1
a1751 1
        13.1.2 Error opening temp file!
d1753 20
a1772 2
        A temporary storage file cannot be opened. Make sure you have at
        least a little disk space left when you run Sentry.
d1775 1
a1775 1
        13.1.3 Error in creating log file!
d1778 4
a1781 4
        created. Make sure you have specified a valid pathname for
        "LogFile" in the Sentry.ini file, and make sure you have some
        free space on your drive. If a log file already exists, it will
        be appended to. Otherwise it will be created.
d1784 1
a1784 1
        13.1.4 Error opening log file!
d1786 6
a1791 3
        There is a problem with the log file. Make sure that the log
        file pointed to by "LogFile" in the Sentry.ini file is not
        write-protected.
d1794 1
a1794 1
        13.1.5 Error opening Sentry.ini file!
d1796 3
a1798 3
        This means that your Sentry.ini file cannot be found. Make sure
        the Sentry.ini file is in the same directory as your Sentry.exe
        file, and that it is named correctly.
d1801 1
a1801 1
        13.1.6 Error in Sentry.ini file! [XXXXXXXX]
d1803 2
a1804 9
        Your Sentry.ini file does not follow the correct format. The
        error message should have a word in square brackets after it
        (IE: [PassFile], [PasswordExpiresIn], etc). This is the
        attribute in the Sentry.ini file that is causing the problems.
        (Sentry expects to find that attribute but doesn't). Use an
        editor to set the attribute correctly. If you are completely
        lost, restore the Sentry.ini file from you backup, or use the
        default attribute setting listed in the comments of the
        Sentry.ini file.
d1807 1
a1807 1
        13.1.7 Registration Error - Program Aborted!
d1809 5
a1813 3
        Someone (probably you) has tried unsuccessfully to change the
        registration information. Very naughty, but if you want to fix
        it, simply restore Sentry.exe from your original copy.
d1816 1
a1816 1
        13.1.8 Error in time stamps.
d1818 1
a1818 9
        This means there is a problem with the time stamps on a user's
        account. You can attempt to manually edit a user's record in the
        Sentry.pwd file, but I don't recommend this. If you don't know
        what you're doing you are more likely to cause additional
        problems than to fix the user. Otherwise, you can try restoring
        your password file from backup. If you continue to use a
        password file that is corrupt, you will probably find you are
        locked out quite frequently. It should be a top priority to fix
        the password file.
d1821 1
a1821 1
        13.1.9 Out of memory!
d1830 7
a1836 1
        13.1.10 This account has expired.
d1838 2
d1843 1
a1843 1
        case, you will have to restore your password file from a backup,
a1846 8
        13.1.11 Internal Screen Error. [Reading|Writing]

        This error should never occur. Having said that, if it does,
        your best bet is to check your video mode. Sentry has only been
        tested in 80x25 text mode, so make sure that is what you are
        using. If this error crops up, please contact me with the
        details.

d1849 2
a1850 2
        When I run Sentry, is displays a warning saying I am using a
        newer/older version of the Sentry.ini file.
d1856 1
a1856 1
        use a Sentry.ini file from a different version.
d1875 2
a1876 2
        Sentry.ini file has been set up correctly. Make sure your
        password file is in the right location.
d1885 1
a1885 1
        My password file is corrupt or deleted.
d1888 1
a1888 1
        should have the password file sent with Sentry. In that case,
a1904 24
        My password file disappeared, but Sentry still works fine!

        A: Your password file is still there, but Sentry has hidden it
        from normal view. When you type "dir" your password file will no
        longer show up. This is done to confuse and mislead any
        potential attackers. If you want to check to make sure it is
        really there, type "dir /a" and it should show up. The log file
        is protected with the same measures.


        I copied my Sentry files to another drive/directory, and now it
        says my password file is not found!

        A: This is (once again) because the password file is hidden.
        When the copy operation was performed, it didn't "find" the
        hidden file and therefore was not copied with the other files.
        Older versions of the DOS copy command can copy hidden files,
        but that function has been removed in later versions. The best
        bet to avoiding this is to re-install Sentry on the destination
        drive/directory and create your accounts from scratch. (There
        are ways to move the password file, but I won't discuss them
        here).


a1916 5

        I have not included a nice simple install program on purpose. If
        you aren't familiar with the basics of DOS, then you probably
        shouldn't be installing Sentry anyway. If there is a need for an
        install program, I may include it in a future release.
@


2.6
log
@Readme file for Sentry V2.6
@
text
@d17 1
a17 1
                                    V2.6
d103 1
d130 1
d1367 12
d1482 8
a1489 8
        -------------------CUT----------------------
        (V2.6) Sentry - Security for DOS/Windows.
        Sentry is a DOS based security program that
        allows you to control and monitor access to
        your PC. It can support up to 100 users and
        has normal and "SuperUser" access. It can
        also be used in Windows to secure the MS-DOS
        icon. Installed correctly, Sentry can be an
d1493 1
a1493 1
        -------------------CUT----------------------
d1566 1
a1566 1
        2.6, Sentry contains over 3150 lines of code. Portability
d1793 8
@


2.5
log
@Sentry V2.5 readme file.
@
text
@d1 1916
a1916 1810
                             ÖÄÄÄÄÄÄÄÄÄÄÄÄ·
                             º Sentry 2.5 º
                             ÓÄÄÄÄÄÄÄÄÄÄÄÄ½
                            Michael A. Bobbitt
                          Mike.Bobbitt@@AcadiaU.Ca
               http://dragon.acadiau.ca/~910318b/Sentry.html

        TABLE OF CONTENTS

        1.0 Introduction
            1.1  Purpose of Sentry
                 1.1.1 In the Home
                 1.1.2 In the Business Environment
            1.2  Features of Sentry
                 1.2.1 General
                 1.2.2 Expiry Dates
            1.3  Distribution of Sentry

        2.0 Setup
            2.1  General Setup Issues
            2.2  The Initial Login
            2.3  First Priorities
            2.4  Using the Sentry.ini file
            2.5  Modifying Your AUTOEXEC.BAT

        3.0 Securing Your Computer
            3.1  BIOS Password
            3.2  Boot Sequence
            3.3  Switches in CONFIG.SYS
            3.4  Passwords
            3.5  The Password File
            3.6  Placement in AUTOEXEC.BAT
            3.7  Keep a Backup

        4.0 Logging In
            4.1  The Login Procedure
            4.2  Changing Passwords

        5.0 The SuperUser Menu
            5.1  Create User
            5.2  Delete User
            5.3  View Users
            5.4  Toggle SuperUser Status
            5.5  Change Account Exipry Date
            5.6  Change Password Expiry Date
            5.7  View Log File
            5.8  Change Account Password
            5.9  Assign Max Invalid Logins
            5.10 Edit Initialization Settings
            5.11 Exit

        6.0 Using Sentry With Windows
            6.1  General
            6.2  Installation Procedure
            6.3  Additional Windows Security
            6.4  Windows 95

        7.0 Securing Other Programs
            7.1  General
            7.2  Setup

        8.0 Creating a new Instance of Sentry

        9.0 Registration

        10.0 Revision History
             10.1  Pre-Release Notes
             10.2  Sentry V1.0
             10.3  Sentry V1.1
             10.4  Sentry V1.2
             10.5  Sentry V1.3
             10.6  Sentry V1.4
             10.7  Sentry V2.0
             10.8  Sentry V2.1
             10.9  Sentry V2.2
             10.10 Sentry V2.3
             10.11 Sentry V2.4

        11.0 Technical Notes
             11.1  Encoding Algorithm
             11.2  Time Stamps
             11.3  Files
             11.4  File_id.diz
             11.5  General

        12.0 Potential Threats To Security
             12.1  The Password File
             12.2  Hardware Loopholes

        13.0 Troubleshooting
             13.1  Error messages
                   13.1.1  Error opening password file!
                   13.1.2  Error opening temp file!
                   13.1.3  Error in creating log file!
                   13.1.4  Error opening log file!
                   13.1.5  Error opening Sentry.ini file!
                   13.1.6  Error in Sentry.ini file! [XXXXXXXX]
                   13.1.7  Registration Error - Program Aborted!
                   13.1.8  Error in time stamps.
                   13.1.9  Out of memory!
                   13.1.10 This account has expired.
             13.2  Other problems

        15.0 Standard Disclaimer

        16.0 Credits

                           ========================


        1.0 Introduction
        ================

        Currently, almost all fields of computer security are growing
        and advancing, with a few notable exceptions. Networks, servers
        and public access systems are all tightening their access to
        avoid potential problems. But what of the single-user PC? Is the
        information contained on these any less valuable? Often times
        not, yet adequate security programs do not exist for PC's. In my
        search for security, I discovered that PC's were virtually
        ignored, and those programs that did exist were weak and faulty.
        Faced with this situation, I decided to write my own security
        program from scratch, incorporating the tightest security
        measures possible, while allowing flexible, easy use.


        1.1 Purpose of Sentry

        Sentry is meant for one basic purpose only: to keep unwanted
        people off your PC. It is flexible enough that this single
        purpose can be used in many different ways, for many different
        reasons. Here are just a few.

        1.1.1 In the Home

        Most people have something on their home PC that they don't want
        others to see. Maybe it's a sensitive document, maybe it's
        copies of e-mail, or maybe you just want to keep track of who is
        using your system. Sentry has the solution for all of these
        problems, by restricting access and logging all attempts to use
        the system.

        Alternatively, sometimes you just want to keep people out,
        period. It could be your nosy room mate, your little brother, or
        your boss at work. In any case, Sentry will keep them out, while
        letting a select group of people in.

        1.1.2 In the Business Environment

        Businesses will find Sentry valuable to guard against
        unauthorized entry into PC's. With Sentry, you can leave your
        terminals unattended while knowing that nobody can access the
        information held on them, unless you want them to. Many
        businesses have cleaners or other independant contractors come
        in during silent hours. A lot of businesses have PC's in open
        areas where a "passer-by" could use them. There's no guarantee
        that these people won't attempt to use your PC's when your're
        not around.

        For businesses that work in groups, Sentry is useful for keeping
        track of who used the PC's and when. Supervisors could have
        SuperUser access on all PC's in their group, allowing them to
        manage and control access as required. Also, the log that Sentry
        keeps could be a valuable tool in determining who was doing
        what, and when.

        You may not need to use Sentry on your system. You might never
        have a security problem to worry about. But the truth is that
        Security isn't something to take a chance on. It is a serious
        problem in today's computing society, and many legitimate users
        find themselves helpless or confused about the real issues. It
        is a shame that the immoral few have ruined it for the rest, but
        we cannot let them get in the way of our daily business. With
        the proper tools and knowledge, we can fight back by closing up
        the common loopholes that attackers use.


        1.2 Features of Sentry

        1.2.1 General

        Sentry will allow you to set up accounts on your computer, one
        account for each person you want to have access. If someone
        doesn't have an account, they don't get in. It's that simple.
        Each person has their own account, with their own password,
        making it easy to track who logs in and when. Since Sentry
        doesn't use a "master access" password, you can wipe a single
        users account without affecting any other users.

        Sentry records each login attempt in a log file which can be
        viewed by a SuperUser at any time.

        1.2.2 Expiry Dates

        You can set accounts to expire on a certain date, effectively
        barring access to the specified user after that. For example, if
        you know that Joe will be leaving on April 14th, you can set his
        account to expire on April 15th. That means you don't have to
        remember to delete his account on the 15th... It will expire on
        it's own, and you can delete it whenever you remember.

        You can also set expiry dates for passwords, meaning that a user
        will have to enter a new password once his old one has expired.
        In addition, you can set the period of time that new passwords
        are good for.

        Sentry can be used to restrict access when you first turn on
        your PC, to block DOS access from within Windows, to secure a
        single program from general use, or any combination of the
        above.


        1.3 Distribution of Sentry

        Sentry is a copywritten piece of work, however distribution of
        the ShareWare version is allowed and encouraged. The only
        stipulation is that it must be unmodified, and must contain all
        of the original files (and no others). Essentially, the .zip
        file you initially recieved is the only format that Sentry is
        distributable in.

        DO NOT distribute any registered versions whatsoever. (By
        distributing a registered version, you are giving out copies of
        a specific encoding scheme, which can be used against the
        registered user).


        2.0 Setup
        =========

        Since you are reading this, I can safely assume you have
        unzipped Sentry. Along with that, I will also assume that you
        have created a directory for Sentry, and that all Sentry files
        are currently in it. (If this is not true, do it now). You may
        want to read the section entitled "Creating a new Instance of
        Sentry" below.


        2.1 General Setup Issues

        The very first thing you should do is make sure you keep a copy
        of all the Sentry files somewhere safe. Copying them to a floppy
        disk and storing it is a good idea.

        The second thing you have to do is to set up the Sentry.ini file
        for your system. You should load the file into a text editor
        (like MS-DOS's edit) and make the changes from there. There are
        instructions and tips provided for each item. Make sure you read
        and understand these instructions before making any changes, as
        an improperly set up Sentry.ini file can cause errors and
        security loopholes.


        2.2 The Initial Login

        Now the next thing you must do is to change the password and
        login provided with the initial copy of Sentry. To do this, you
        must run the Sentry.exe program. If it displays an error
        message, check the troubleshooting section at the end of this
        file.

        When it asks for a login, use "Sentry", with the password
        "Sentry". You can turn case sensitivity off in the Sentry.ini
        file, but for logins only. The password must be entered exactly
        as shown (sentry or SENTRY will not work). The Sentry account
        has SuperUser access, meaning you can create and delete accounts
        while logged in as Sentry. To log in as a SuperUser, enter
        Sentry for a login, and instead of pressing enter, hold down the
        CONTROL key and press enter. This tells the Sentry program that
        you want to log in as a SuperUser. Then enter your password
        normally, and instead of dropping to DOS, you will go to the
        SuperUser menu. (See the section below on "The SuperUser Menu"
        for more information).

        From here, you should create a new user (you) and grant yourself
        SuperUser access. You can do this during creation by holding the
        CTRL key while pressing enter after typing your login name. You
        can also do this by using the "Create User" option normally and
        then using the "Toggle SuperUser Access" menu option to give
        yourself SuperUser privileges.


        2.3 First Priorities

        Once you have your account set up, you should delete the Sentry
        account, so nobody else can use it. This is very important as a
        potential intruder will probably try to enter through the
        default Sentry account first. (If you delete it, that closes the
        loophole).

        Sentry will not let you delete the last SuperUser, so you must
        create a new user with SuperUser access before deleting the
        Sentry account.

        From here, you can create the other users of your system, and
        define their starting passwords, expiry dates and access rights.
        See the section below on "The SuperUser Menu" for more
        information.


        2.4 Using the Sentry.ini file

        Sentry can be configured to your needs by way of the Sentry.ini
        file. This file contains information that you may wish to
        change, allowing Sentry to adapt to many different situations.

        The Sentry.ini file follows a very specific format, and if you
        deviate from it, Sentry will not work! Comments are allowed, as
        long as the comment line begins with a * character. Blank lines
        are also permitted. The order of the items in the Sentry.ini
        file is critical. Do not move items around. The comments
        provided with the Sentry.ini file will guide you through this
        stage. Feel free to add your own comment lines as you see fit.

        If this is too much for you, then you can edit the Sentry.ini
        file from the SuperUser menu. You can do this by selecting the
        "Edit Initialization Settings" option (see section 5.10). Many
        people find this easier than editing the actual file. Any
        changes you make will not take effect until the next time you
        use Sentry.


        2.5 Modifying Your AUTOEXEC.BAT

        Simply add the following line to the top of your AUTOEXEC.BAT
        file:

        ----------------- CUT ----------------
        \Sentry\Sentry
        ----------------- CUT ----------------

        The above example assumes you have installed Sentry on
        c:\Sentry, which may not be true. Adjust the path in the first
        line to reflect the location of Sentry on your system.

        NOTE: These lines MUST be the first lines in your autoexec.bat
        file. If not, the user may be given a chance to bypass Sentry by
        pressing CTRL-C or CTRL-BREAK.

        If Sentry is installed on a drive other than the one you boot
        from (drive D in the example below), then add these lines
        instead:

        ----------------- CUT ----------------
        d:
        \Sentry\Sentry
        c:
        ----------------- CUT ----------------


        3.0 Securing Your Computer
        ==========================

        Sentry is essentially useless unless you take the appropriate
        additional security measures for your machine. Below I have
        outlined some of the things you can do to increase the security
        of your system.


        3.1 BIOS Password

        Protect your BIOS! It has a built in password, so set it!
        Without the password, any user can get into your BIOS and change
        your critical system settings. I have seen several different
        types of BIOS setups, but generally, you use the CHANGE PASSWORD
        command (Sometimes also listed as SUPERVISOR PASSWORD) from the
        main menu and set the SECURITY OPTION to setup (as opposed to
        system) in the BIOS FEATURES SETUP screen. Depending on the
        layout of your BIOS, you may have a CHANGE SETUP PASSWORD option
        right on the main menu.


        3.2 Boot Sequence

        Change your boot sequence. Again, in your BIOS, under the BIOS
        FEATURES SETUP screen, set your BOOT SEQUENCE to boot from your
        hard drive first. (This usually means set it to C,A as opposed
        to A,C). This will ensure that no-one can bypass Sentry by means
        of a boot disk.


        3.3 Switches in CONFIG.SYS

        Add "switches /n/f" as the first line of your CONFIG.SYS file.
        The /n will dis-allow pressing F8 to step through the CONFIG.SYS
        and AUTOEXEC.BAT files. This means that users cannot bypass
        Sentry by this method. The /f switch is optional, it simply
        speeds up your boot-up time (by about 2 seconds).


        3.4 Passwords

        Pick a good password. Short passwords are a bad idea, as well as
        birthdays, girlfriends names, etc. Anything that is easy to
        guess should be avoided. Good passwords are not words at all,
        but made up from a "mnemonic" sentence. For example, the
        sentence "I'll wait for you" turns into "Illw84u" (trust me).
        Mixing lower case letters, upper case letters, and numbers
        increases the security of a password, and passwords of this type
        are near impossible to guess or crack. Do not write your
        password down, especially near your computer. Try to memorize it
        if possible. Change your password, but not too often. People who
        change their passwords too often (less than 6 months or so) tend
        to write them down, which is a bigger risk. Don't enter your
        password with someone looking over your shoulder. If someone is
        in the room, block their view, or wait until they leave.


        3.5 The Password File

        Put your password file in a safe place. Although passwords are
        encoded, usernames and time stamps are not. Also remember, the
        encoding scheme is one way only, so if I encode login names, you
        will never be able to view who is in your password file (IE: you
        would have to "guess" which person to delete). Users can change
        time stamps in the password file, and this can cause serious
        problems, so KEEP IT SAFE!

        NOTE: Sentry automatically hides your password file for you.
        After you have run Sentry once, your password file (and log
        file) will not appear in directory listings. This will help your
        security, but is not a fool-proof method.


        3.6 Placement in AUTOEXEC.BAT

        When you are installing Sentry, make sure it is the FIRST file
        in your AUTOEXEC.BAT! Otherwise, the user may be able to exit
        when another program is running and avoid Sentry all together!


        3.7 Keep a Backup

        Keep a backup copy of all your Sentry files! Especially your
        password file! If something happens to these files, you may be
        locked out your computer if you don't have a backup.


        4.0 Logging In
        ==============

        4.1 The Login Procedure

        When you first run Sentry, you should see the standard startup
        screen. Your registration information is contained here. (The
        shareware release simply says it is registered to Shareware).
        You should also see a prompt asking you to enter your login (or
        user name). If instead you see an error message, check at the
        end of this file for help.

        While entering your user name, if you have SuperUser access, you
        can log in as such. You can do this by holding down the CTRL key
        while pressing enter. If you do not have SuperUser access, or do
        not wish to log in as such, simply press enter. In either case,
        this will send you to the password prompt.

        Once you have reached the password prompt, you simply enter your
        password, and hit enter when you are finished. Your password is
        not echoed to the screen. At this time, the date and time of
        your last login will be displayed.

        The minimum and maximum length of both the login and password
        are set by the "MinPasswordLen" and "MaxPasswordLen" attributes
        in the Sentry.ini file respectively.

        If there have been any invalid login attempts made against your
        account since the last valid login, you will be told so, and how
        many. If the number of invalid login attempts against your
        account has exceeded the maximum allowed, your account will be
        locked out until the SuperUser resets it.

        If your account has expired, it will say so, and subsequently
        lock you out. If your password has expired, it will also say so,
        but will then prompt you to enter a new password. You may not
        re-use your old password, and you must pick a password that
        corresponds to the length limits set out in the Sentry.ini file.
        Once you have entered and verified your new password, it is
        given a new expiry date according to the "PasswordExpiresIn"
        value in the Sentry.ini file.

        If you have logged in as a SuperUser, and have SuperUser access,
        you will now be in the SuperUser menu (see the section below).
        If not, you will simply be dropped to DOS, and the login
        procedure is complete.


        4.2 Changing Passwords

        If you wish to change your password at any time, you can do so
        by entering the pass key. The pass key is defined in the
        Sentry.ini file, and is displayed when Sentry starts up. To
        change your password, simply enter your user name as usual, and
        when prompted for your password, enter the pass key. You will
        then be prompted for your old  password (to make sure it is
        really you), and then you will be asked for your new password,
        which will be verified and saved to disk. Your new password will
        expire in the number of days designated by "PasswordExpiresIn"
        in the Sentry.ini file.

        Changing your password has no effect on SuperUser access.


        5.0 The SuperUser Menu
        ======================

        5.1 Create User

        This option allows you to create users on your system. First of
        all, you must enter the username (or login) you wish to assign
        to that user. If you wish to create a user with SuperUser
        status, type in the username and hold down the CONTROL key when
        pressing enter. Otherwise, just press enter when you're finished
        at the login prompt. Once that is complete, Sentry asks for the
        password. The password is not echoed to the screen. The user
        should choose and enter their own password. SuperUsers need not
        know what the passwords are since they can still manage the
        accounts without knowing them. The password is entered twice to
        ensure no typos were made, and then saved to the password file
        in encoded form. The ESCAPE key will abort this operation at any
        time.

        Note: There is currently a maximum of 100 users allowed. This
        limit can be bypassed if required (contact me for a larger
        capacity version).


        5.2 Delete User

        The delete option is very simple. It brings up a list of all
        users, and you simply use the cursor keys to highlight the user
        you wish to delete. SuperUsers are denoted by a * to the right
        of their username. Press enter to select the appropriate user.
        If the selected user is a SuperUser, Sentry will give a warning.
        SuperUser or not, Sentry will then ask if you are sure you want
        to delete them. Any input other than a 'y' will not perform the
        delete. The ESCAPE key will abort this option at any time.


        5.3 View Users

        This option allows you to view all users who currently have
        accounts on your system. SuperUsers are again denoted by a * to
        the right of their login name. The last login date/time, account
        expiry date and password expiry date are also shown to the right
        of the user's login name. In addition, the number of invalid
        logins since the users last valid login are shown with the
        number of invalid logins allowed before an account is locked up.
        An "X" in the "Max Inv Log" (Maximum Number of Invalid Logins
        Allowed) column means there is no limit. You can use the PAGE UP
        and PAGE DOWN keys to scroll forward and back if there are
        multiple pages of users. Arrows ( and ) will be present if
        there are additional pages above and/or below. The ESCAPE key
        will exit back to the main menu.


        5.4 Toggle SuperUser Status

        When this option is selected, it first brings up a list of all
        users on the system. Again, SuperUsers are denoted by a *. Once
        you have selected a user, Sentry will ask you if you want to
        grant/revoke SuperUser access to/from the appropriate user. Any
        input other than a 'y' will not change that users status. Now
        the user must enter a password. (Since the SuperUser status is
        encoded in the password, and the password can never be decoded,
        I can't change SuperUser access without resetting the password).
        The user can re-enter their old password, or enter a new one
        (the old one will be over-written). In a worst case scenario,
        the SuperUser can re-assign a new password to the user if he is
        unavailable to enter a new password himself. (A hostile user can
        have SuperUser access revoked without having to enter a new
        password; you can do it for him).


        5.5 Change Account Expiry Date

        This option lets you define when an account will expire on your
        system. Expired accounts no longer have access. This option is
        useful if a user will be leaving. Then you don't have to
        remember to delete their account on the day they leave. You can
        set it to expire, and delete it when you remember.

        This option also works in conjunction with the "Assign Max
        Invalid Logins" option. Once an account reaches it's maximum
        number of sequential invalid logins, it expires. The only way to
        re-activate the account is to change the expiry date with this
        option.

        Once you select this option, some information about the account
        will be displayed. If it is a SuperUser account, Sentry will
        tell you so. It will then display the account's current expiry
        date. You will be asked if you are sure you want to change that
        user's expiry date. Any input other than a 'y' will abort the
        process, otherwise you will be prompted for the year the account
        will expire. The year must be entered as 4 digits (IE: 1997). If
        you enter 'N' at the year prompt, no expiry date is assigned to
        that account (it is valid forever). If you enter a valid year,
        you will then be prompted for the expiry month, which is entered
        as 2 digits (IE: 06 for June) followed by the expiry day, which
        is also entered as 2 digits. Accounts expire at one second past
        midnight on the date of expiry.


        5.6 Change Password Expiry Date

        This option lets you define when a users password will expire.
        Once the password has expired, the user must enter a new one.
        This forces the user to change their password. Once a password
        has expired, the next time the user logs in he will be forced to
        enter a new password. The new password is valid for the number
        of days set in the "PasswordExpiresIn" option in the Sentry.ini
        file. Once a password has expired, the user cannot re-enter it.
        He must select a new password. (NOTE: Sentry does not keep
        historical records on passwords, so a user may alternate back
        and forth between 2 passwords. This is not a secure practice and
        should be avoided).

        Once you select this option, some information about the account
        will be displayed. If it is a SuperUser account, Sentry will
        tell you so. It will then display the current expiry date for
        the password. You will be asked if you are sure you want to
        change that user's expiry date. Any input other than a 'y' will
        abort the process, otherwise you will be prompted for the year
        the password will expire. The year must be entered as 4 digits
        (IE: 1997). If you enter 'N' at the year prompt, no expiry date
        is assigned to that password (it is valid forever). If you enter
        a valid year, you will then be prompted for the expiry month,
        which is entered as 2 digits (IE: 06 for June) followed by the
        expiry day, which is also entered as 2 digits. Passwords expire
        at one second past midnight on the date of expiry.


        5.7 View Log File

        Every time a user logs in, a record is kept on disk. If you want
        to view that online record, select this option. The log file
        will be displayed, one screen at a time. Once the entire log
        file has been displayed, Sentry will ask you if you want to
        clear the log file. Any input other than 'y' will exit, leaving
        the log file in tact. If you answer with a 'y', Sentry will
        clear out the old entries. This should be done fairly
        frequently, depending on how busy your system is. Large log
        files take up more disk space.

        You should always keep a close eye on the log file as this will
        often tell you when something is wrong on your system. All error
        messages are saved to the log file, so you can see if Sentry has
        run into any problems. Also, it records the current time, and
        the username of the user attempting to log in. This will help
        you to identify any potential attacks on your system. The log
        file is hidden by Sentry, but you should also place it somewhere
        safe so that users cannot tamper with it. You can set the
        location of the log file with the Sentry.ini file.


        5.8 Change Account Password

        This option allows the SuperUser to change an account's
        password, in case the user forgot it, or some other strange
        disaster has occurred. When assigning a new password to an
        account, you should set the expiry date to be immediatly, so the
        user is forced to choose a new one. If the previous password had
        no expiry date, none is assigned to the new password. Otherwise
        the password expires in the number of days assigned to
        "PasswordExpiresIn" in the Sentry.ini file. You can abort at any
        time by pressing the ESCAPE key.


        5.9 Assign Max Invalid Logins

        This allows you to set the maximum number of invalid logins
        allowed before an account is disabled. The default number is
        defined in the Sentry.ini file ("InvalidLogins") and is assigned
        to all accounts when they are first used.

        To assign a new maximum, simply select the "Assign Max Invalid
        Logins" option from the SuperUser menu. From here you will be
        shown the complete user list, and asked to select the user you
        wish to change. Pressing the ESCAPE key will abort the operation
        here.

        Once you have selected the user, you will be informed if that
        user is a SuperUser. NOTE: You should not assign a maximum
        number of invalid logins to your last SuperUser account. If you
        do, and someone attempts to break in to that account, you could
        be locked out of the SuperUser menu!

        Next you will be told what the user's current max invalid login
        setting is, and asked if you want to change it. Any input other
        than a 'Y' will abort the operation. Now you will be asked to
        enter the number of invalid login attempts before an account is
        disabled. Entering 'N' or a 0 will mean that there can be
        unlimited invalid login attempts made.

        Please note that a value of less than 10 may cause you more
        trouble than good. You may be spending a lot of time re-setting
        accounts if you pick too low a value, so consider this
        carefully. Also note that when an account is locked up, it is
        actually set to expire immediately. As a result, if you wish to
        re-activate an account, you must change the account's expiry
        date (see above). This is also handy for determining when the
        account was actually de-activated. The expiry date for that
        account it set the the day it was locked out.

        Every time a successful login is made to an account, the invalid
        login counter is reset. This means that an account will not be
        locked out if it has a valid login before the maximum is
        reached. (For example, say an account has a maximum of 10
        invalid logins. If there are 7 invalid logins before a
        successful login, and then 5 more invalid logins, the account
        will not be locked up. There must be 10 sequential invalid
        logins for the account to be disabled.)

        Once you have finished making the change, you can view the user
        list to make sure it is acceptable.


        5.10 Edit Initialization Settings

        This option allows you to edit the Sentry.ini file from within
        Sentry. Once this option is selected, all of the attributes from
        the Sentry.ini file are displayed. Simply select the attribute
        you wish to modify, and you will be given the following
        information:

                - A one line description of the attribute.

                - The name of the attribute as it appears in the
                  Sentry.ini file. This will appear in brackets under
                  the one-line description.

                - A brief description of the attribute and it's uses.

                - Valid settings for the attribute, if applicable.

                - Any security notes, if applicable.

                - The default value for the attribute.

                - The current value for the attribute.

        At this time, you will be prompted to enter a new value for the
        attribute. Pressing ENTER on a blank line, or pressing the ESC
        key abort any changes the current value.

        Sentry performs strict checking on the values you enter, and
        will not save an invalid value. For this reason, you should
        change your Sentry.ini settings from the SuperUser menu whenever
        possible.


        5.11 Exit

        This simply returns you to the DOS prompt. It is the same as
        pressing the ESCAPE key.


        6.0 Using Sentry With Windows
        =============================

        6.1 General

        Sentry is also adaptable to Windows, allowing you to keep users
        away from DOS. This may be desirable if you enter Windows
        immediatly upon startup (I.E.: your autoexec.bat contains "win"
        as a command). If you want to limit access to your system as a
        whole, you could install Sentry in the usual way. This would
        keep out unwanted users all together. If you want to also limit
        access to the DOS prompt from Windows, you can do that too. All
        you must do is create a new instance of Sentry (see below), and
        then simply set up your windows to run Sentry when you drop to
        DOS. The example setup below assumes you have installed an
        instance of Sentry in c:\Sentry\Inst1, but you can substitute
        your actual directory names in where applicable.


        6.2 Installation Procedure

        Installing Sentry in the Windows environment is simple. Included
        in the Sentry zip file are 2 files:

        Sentry.grp
        Sentry.pif

        Copy both of these files into your windows directory. Now, enter
        Windows and from the Program Manager, select [F]ile, then [N]ew.
        Next select Program Group. When prompted, enter "Sentry" for
        both description and file name. Now you should see a new program
        group called Sentry. The Sentry program group should contain a
        single icon, labelled MS-DOS. This icon actually points to
        sentry.pif, which contains specific information about running
        Sentry.

        You can edit the new icon (highlight it and press ALT-ENTER) and
        change the working directory to point to your Sentry files.

        IE: c:\Sentry, or c:\Sentry\Inst1, etc.

        From here, run the Pif Editor program (the icon is a little
        tag), and open Sentry.pif. Now change the "Program Filename" to
        point to your Sentry.exe file.

        IE: c:\Sentry\Sentry.exe, or c:\Sentry\Inst1\Sentry.exe, etc.

        In Addition, change the "Working Directory" to be the same as
        the working directory for the icon (see above). Once you save
        the .pif file, you are all set.

        At this point you should test out the new Sentry icon to make
        sure it works ok. When you double click on the new icon, it
        shoould take you directly to Sentry. Once you have entered a
        correct username and password, it will then drop you to a
        regular DOS shell. You can type "EXIT" to return to Windows at
        any time.

        Once you are sure it works, remove your old MS-DOS icon, so that
        users cannot use it to drop straight to DOS. You can drag your
        new icon into the same location as your old MS-DOS icon, so
        everything will look the same.

        Now there is one last step. If a user were to exit Windows, they
        would be at the DOS level, which is not what we want. Since your
        autoexec.bat file is running windows on startup, you can block
        people from exiting by forcing them to go through Sentry. You
        can do this by adding a call to Sentry after the win command in
        your autoexec.bat.

        For example, the last few lines of your autoexec.bat might look
        like this:

        ----------------- CUT ----------------
        win
        \Sentry\Inst1\Sentry
        ----------------- CUT ----------------

        Alternatively, you can add the security measures described in
        section 6.3 below.

        And that's it. If it seems like a complicated process, just try
        the steps one at a time, and make sure everything works ok. The
        end result is that when you click on the MS-DOS icon, it will
        run Sentry before dropping you to the DOS shell. That means that
        you can limit access to the operating system, without pulling
        any fancy tricks in Windows. Since you have made a new instance
        of Sentry, you could have one instance run when you boot up
        (giving access to windows), and have another instance run when
        you click on the DOS icon (giving access to the operating
        system). That way, a user that has access to windows may not be
        able to drop to DOS.

        Be warned however that Sentry will still lock up your system
        when a user fails to log in. This may cause you to lose any
        information you have not saved in your Windows session, if
        Windows becomes unstable.

        If Sentry does lock up your system, you may be able to recover
        back to Windows by pressing CTRL-ALT-DELETE and closing the DOS
        prompt. This will still not allow access to DOS, but you will
        not lose anything you were working on.


        6.3 Additional Windows Security

        There are additional security measures built into Windows that
        should be considered when using Sentry. After all, securing the
        MS-DOS icon won't do any good if someone can edit it back to the
        way it was.

        To add more security to your Windows system, just add this
        Restriction section to your progman.ini file:

        ----------------- CUT ----------------
        [Restrictions]

        EditLevel=4
        rem Stops the creation, movement, copying, deletion, or
        rem modification of ANY groups or icons.

        Noclose=1
        rem Prevents a user from exiting windows.

        NoRun=1
        rem Disables the run command selection from the file menu.

        NoSave=1
        rem Stops the selection of save settings on exit from program
        rem manager.

        NoSaveSettings=1
        rem Disables the save settings on exit command, so any changes
        rem made to the your program manager group icons and windows
        rem cannot be saved upon exiting windows.
        ----------------- CUT ----------------

        To nulify any of these entries, remove it or change the value
        from 1 to 0.  You can delete the file manager Icon as an
        additonal security precation.


        6.4 Windows 95

        Sentry is easily adaptable to use in a Windows 95 environment.
        In most respects, the setup is the same as in a DOS/Windows
        environment.

        As before, ensure that the call to Sentry is at the beginning of
        your AUTOEXEC.BAT file. The Sentry.pif file and Sentry.grp file
        will still work with Windows 95, although at this time I have
        not drawn up specific instructions for installation.

        I have not yet conducted thorough tests in a Windows 95
        environment, however documentation for this should be
        forthcoming in a future revision.


        7.0 Securing Other Programs
        ===========================

        7.1 General

        In some cases, it might be beneficial to secure a single
        program. It might be a word-processor, a mail program, or even
        Windows. In any case, you can secure it with Sentry, even if you
        don't use Sentry during boot-up. You will probably want to
        create a new instance of Sentry (see below) for each program you
        want to secure. That will allow you to have different accounts
        and passwords for each program.


        7.2 Setup

        To set this up, all you have to do is write a batch file of the
        following format, and stick it in a directory in your path.
        (C:\DOS is almost always in your path, so you could stick these
        batch files there). In this example, we will secure the program
        called RUNME (loacted at C:\prog\runme.exe):

        ----------BEGIN RUNME.BAT-----------------
        @@echo off
        c:
        \Sentry\Inst2\Sentry
        cd \prog
        runme
        cd \
        -----------END RUNME.BAT------------------

        The program as shown above will run Sentry before it runs
        RUNME.EXE. As long at the batch file is in your path ahead of
        RUNME.EXE, RUNME.BAT will execute first, barring the user from
        running RUNME.EXE without running Sentry first. C:\DOS is almost
        always first in your path, so this will work for everything but
        DOS programs. You can add a new directory to you path by editing
        your AUTOEXEC.BAT. If you add it to the beginning, and place all
        your batch files there, they will run first. The only exception
        to this rule is that if the user is in the directory containing
        RUNME.EXE they will not execute RUNME.BAT first.

        This is not by any means a perfect method of securing a program.
        It will work in most cases, but with the proper knowledge and
        patience, this method can be defeated. If your users are
        skilled, don't rely on this method to be "bullet-proof." (Sentry
        was not designed for this purpose, it is merely an additional
        use).

        Future versions of Sentry may have an "automated" method for
        doing this if the need exists.


        8.0 Creating a new Instance of Sentry
        =====================================

        In some of the scenarios listed above, you may be required to
        create a new "instance" of Sentry. That is to say, a completely
        new copy of Sentry, that works independantly of all other
        copies. This is a fairly simple process, that you can perform as
        many times as required.

        The first thing you must do when creating a new instance is to
        create the directory you wish to place it under. If you plan to
        have several instances, you may want to create a Sentry main
        directory, with your instances branching off of that. For
        example:

        c:\Sentry
             |
             +----+------- Inst1
                  |
                  +------- Inst2

        This will allow you to keep all your Sentry files well
        organized, and seperate from your other programs. Create a
        directory for each instance you anticipate you will need. From
        there, simply copy ALL of the Sentry files into each directory.
        The final step is to set up the accounts of each instance
        according to your needs. To do this, you must go into each
        directory individually and run Sentry. Now log in as a SuperUser
        and set up all the required accounts. Remember that each
        instance is independant of the others. Your password file should
        not be the same for any 2 instances (otherwise there is no
        advantage to having 2 instances). That means that the PassFile
        setting in each Sentry.ini must be different, and your password
        files must be in different locations. For simplicity's sake, you
        may want to keep your password file for each instance in the
        same directory as the other related Sentry files. (The password
        file for Instance 1 goes into c:\Sentry\Inst1, and so on).

        You should always test out each instance and make sure it works
        before using it.


        9.0 Registration
        ================

        If you use Sentry on your machine(s), I urge you to register. I
        have put a lot of time and effort into making Sentry a viable
        security program, and I would appreciate the effort very much.

        On the other hand, I realize that not everyone can afford to
        register. In that case, please feel free to continue to use the
        ShareWare version. There are no limitations on how long or how
        many times it can be used. My intention with Sentry was to make
        a contribution to PC security, and to make it available to
        everyone. All I ask is that if you use Sentry, and are able,
        please register.

        The shareware version of Sentry has all the functionality of the
        registered version, with one exception: it does not encode
        passwords. This will allow you to test out all the functions of
        Sentry before you commit to purchasing it. The ShareWare version
        in itself is a very secure program as is, however if you are
        serious about Security, plaintext passwords are not a viable
        option.

        To order, simply fill out the order form provided (Order.frm)
        and e-mail or snail-mail a copy to me.

        As a registered user, you will receive:

              - The full Sentry program (with password encryption) and
                related files on 3.5" disk.

              - A laser printed user's manual (essentially this file,
                with a few changes in format and content).

              - Online internet support via e-mail.

              - Free upgrades as soon as they are available.

              - Notices about any potential security risks, and
                instructions on how to protect yourself.

              - The ability to request specific features in future
                versions of Sentry.

        NOTE: Registered versions are not inter-compatible. That is,
        user X's password file is encrypted differently than user Y's
        password file. The version of Sentry that you recieve is good
        only for you and your files. (Likewise, nobody else can use
        their copy of Sentry with your password file). See the order
        form for information on obtaining compatible versions of Sentry.


        10.0 Revision History
        =====================

        10.1 Pre-Release Notes

        March 95   - My search for DOS security programs is
                     unsuccessful. The general idea for Sentry is
                     formed.

        April 95   - Coding for Sentry begins.

        May 95     - Still coding...

        June 95    - Sentry is now a complete program.

        July 95    - Beta testing. Many updates made.


        10.2 Sentry V1.0

        Release Date: 20 July 95


        - Sentry V1.0 (Shareware) is released. Contains basic
          functionality. At this point, Sentry is approximately 1700
          lines of code.


        10.3 Sentry V1.1

        Release Date: 27 July 95

        - Sentry V1.1 Released. V1.1 fixes some serious bugs in V1.0,
          and has these additions:

                     * Date format is selectable.

                     * Users with no password expiration are not
                       assigned an expiry date on entering a new
                       password.

                     * Incorrect password verification displayed
                       immediately when creating a new user, or toggling
                       SuperUser status.


        10.4 Sentry V1.2

        Release Date: 29 July 95

        - Sentry V1.2 Released. Some more minor bugs are repaired and
          several areas are updated. Additions are:

                     * Memory management improved.

                     * All user stats now shown instead of just login
                       name.

                     * The keyboard buffer is flushed after an invalid
                       login attempt.


        10.5 Sentry V1.3

        Release Date: 01 Aug 95

        - Sentry V1.3 Released. Again, more bugs were fixed in this
          version. Additions are:

                     * The log file is now much more detailed than
                       before, and includes a time stamp on every
                       action.

                     * A bug with deleting a user listed as 15th or
                       later in the password file has been fixed.
                       (Regardless of what page the user you selected to
                       delete was on, a user from the first page was
                       always deleted).

                     * A bug in the multi-user display was fixed. (If
                       the last page contained one user, you could not
                       page down to see him).


        10.6 Sentry V1.4

        Release Date: 08 Aug 95

        - Sentry V1.4 Released. Some minor changes have been made,
          mostly for the sake of appearance. Additions are:

                     * The Sentry.ini file now allows the user to select
                       the colours to be used for normal and highlighted
                       text.

                     * Input routines have been improved and simplified.
                       Inapropriate characters have been stripped from
                       the input stream.


        10.7 Sentry V2.0

        Releaase Date: 11 Aug 95

        - Sentry V2.0 Released. Many revisions, fixes and additions have
          been made to the program for this release. Most of the update
          ideas came from Bret Jacobsen. Additions include:

                     * Invalid login/password length messages (both to
                       the screen and log file) are user-definable in
                       the Sentry.ini file.

                     * If a normal user attempts to log in as a
                       SuperUser, it is recorded in the log file.

                     * The SuperUser Login flag is cleared after an
                       invalid login. (This is a bug fix: previously if
                       CTRL-ENTER was pressed during an invalid login
                       attempt, the next successful login attempt would
                       be as a SuperUser, as long as the user had
                       access).

                     * A bug with the Toggle SuperUser Access option
                       corrupting the time stamps has been fixed.

                     * The log file is again re-organized to be more
                       "readable."

                     * You can no longer delete the last SuperUser on
                       your system (thereby locking yourself out).
                       Sentry performs a check previous to deletion and
                       will abort if you are deleting the last
                       SuperUser.

                     * A bug with the input skipping characters was
                       fixed.

                     * After a successful login, the number of invalid
                       login attempts since your last successful login
                       is now shown.

                     * The user can now abort a password change, unless
                       the password has expired.

                     * The option to reset an account's password has
                       been added to the SuperUser menu.

                     * You can now define the number of invalid logins
                       permissible before an account expires (locks up).
                       The default setting is defined in the Sentry.ini
                       file, and the settings for individual accounts
                       can be modified from the SuperUser menu.


        10.8 Sentry V2.1

        Releaase Date: 20 Aug 95

        - Sentry V2.1 Released. Changes include:

                     * Input no longer automatically ends after
                       "MaxPasswordLen" characters have been entered at
                       the login or password prompts. Input continues as
                       required, however only "MaxPasswordLen"
                       characters are used. Any extra characters are
                       discarded.

                     * Case sensitivity for logins can now be turned on
                       and off via the Sentry.ini file. This is
                       applicable to logins only, passwords are still
                       case sensitive.


        10.9 Sentry V2.2

        Releaase Date: 10 Sep 95

        - Sentry V2.2 Released. Changes include:

                     * Sentry now uses windowed screens for all output,
                       as opposed to simply directing output to the
                       entire screen.

                     * When entering dates, the year is now checked. If
                       it is not 4 characters, the user is forced to
                       re-enter it. This was causing problems with
                       Sentry accepting '96' as a valid year, and
                       subsequently not translating correctly.

                     * A bug with the password encoding scheme has been
                       fixed. The encryption used to truncate passwords
                       at length 8, causing only the first 8 characters
                       to be recognized. For SuperUsers, this meant that
                       passwords over 8 would not contain the SuperUser
                       stamp (it was truncated). This problem has now
                       been rectified, and passwords are significant for
                       MaxPasswordLen characters. All in all, this
                       seriously increases the amount of security
                       available from Sentry.

                       NOTE: Because of the above modification, older
                       versions of Sentry cannot use password files from
                       V2.2 and up. The reverse is not true however, as
                       Sentry V2.2 can use password files all the way
                       back to V1.0.

                       Also note that to use passwords over 8
                       characters, you must re-create the old passwords.
                       This can be easily done by selecting the "Change
                       Account Password" option from the SuperUser menu.


        10.10 Sentry V2.3

        Releaase Date: 24 Sep 95

        - Sentry V2.3 Released. Changes include:

                     * Small bugs with windowed mode have been fixed.

                     * Windowed mode is now optional. For those that
                       prefer "normal" operation, you can set that in
                       the Sentry.ini file.

                     * Log file viewing can now handle long lines, and
                       you can skip to the end of the file by pressing
                       the ESC key once.

                     * Quickstart instructions are now included in the
                       Qstart.txt file.


        10.11 Sentry V2.4

        Releaase Date: 06 Oct 95

        - Sentry V2.4 Released. Changes include:

                     * The Sentry.ini file can now be edited from the
                       SuperUser menu. The user can get information on
                       each attribute, including a brief description,
                       security notes, default setting, and the current
                       setting just by selecting which attribute they
                       wish to change.



        10.12 Sentry V2.5

        Releaase Date: 10 Oct 95

        - Sentry V2.5 Released. Changes include:

                     * Sentry can now be run from any location. The user
                       does not have to be in the Sentry home directory
                       for it to work properly.

        11.0 Technical Notes
        ====================

        11.1 Encoding Algorithm

        The encoding algorithm used is the standard UNIX crypt()
        algorithm. It is a one-way encoding algorithm that incorporates
        the Data Encryption Standard (DES) and RSA technology. It is
        used on UNIX systems to secure passwords. (As a note, the
        encryption code is not included with the ShareWare version, so
        no amount of examining the code will reveal the algorithm).

        The users' passwords are never decoded. They are stored on disk
        and in memory in an encoded format. The entered passwords are
        encoded using the same algorithm and matched in an encoded form.
        This prevents disk or memory scans from revealing the password
        to prying eyes.

        I have begun running some tests on cracking the passwords, and I
        will include my results. So far, this is what I have found:

        Password Length          Maximum Time to Break
        ------------------------------------------------
        4                        22 days
        5                        1368 days or 3.75 years
        6                        232.4 years
        7                        14409 years
        8                        893357 years

        All times listed are approximated as using a Pentium 90MHz CPU
        and an alpha-numeric password.

        These figures may be adjusted as my testing becomes more
        accurate. The above figures also assume you know the length of
        the password, which cannot be determined by looking at the
        encrypted version. As a result, the search time may be much
        greater.

        SuperUser access is also encoded in the password. I tried many
        different ways before finally settling on this. It is the most
        secure method. Actually, SuperUser access is stored on the
        password (which is then encoded), and then stored again on the
        encoded password. That looks like:

        password                      <-- Password as entered.

        super(password)               <-- Password with SuperUser stamp.
                                          * This is the stamp that is
                                          used to determine access.

        crypt(super(password))        <-- Encoded password password with
                                          SuperUser stamp.

        super(crypt(super(password))) <-- SuperUser stamped encoded
                                           password with SuperUser
                                           stamp.
                                           * This is the stamp that is
                                           used to "see" who has
                                           SuperUser access.

        That way when you use the "View Users" command, you can see
        which ones are SuperUsers. However, since the non-encoded
        SuperUser stamp can be edited, it is only used for viewing. The
        encoded SuperUser stamp is used for access. If anyone attempts
        to alter the non-encoded stamp, a warning will be displayed in
        the log file each time that user logs in.


        11.2 Time Stamps

        The time stamps used in Sentry are in the standard UNIX format.
        That is, the number of seconds since 01 Jan 1970 00:00:00.

        NOTE: I have found one date which always seems to cause an
        error. 01/01/1997 translates to 01/15/1995 (1st day of the 15th
        month of 1997). This is obviously incorrect. I have determined
        it is a bug in Borland's date conversion routines. It is the
        ONLY date that causes problems, to my knowledge, all others
        translate fine. I advise against using 01/01/1997 for any expiry
        dates.


        11.3 Files

        The following files are included with this release of Sentry:

        Sentry.exe      This is the executable program.
        Sentry.ini      The initialization file.
        Sentry.pwd      The password file.
        Sentry.pif      The Sentry .pif file for Windows.
        Sentry.grp      The Sentry Group file for Windows.
        File_id.diz     Short description file.
        Order.frm       The order form.
        Readme.com      Displays this file.
        Readme.txt      This file.
        Qstart.txt      Quickstart instructions.
        Whatsnew.txt    A short description of modifications to the
                        latest version.

        If you do not have all of these files, Sentry will probably not
        work for you. You can pick up a complete copy of Sentry (and
        updates as they become available) at:

              http://dragon.acadiau.ca/~910318b/Sentry.html


        11.4 File_id.diz

        The actual contents of the file_id.diz file are shown below. If
        any modification has been made to the original file, please
        re-create it from the following section.

        NOTE: this is primarily for SysOps of BBS's. Single users can
        delete the file_id.diz if they wish. (However, please make sure
        that all files are present if you distribute the program.)

        -------------------CUT----------------------
        (V2.5) Sentry - Security for DOS/Windows
        Sentry is a DOS based security program that
        allows you to control and monitor access to
        your PC. It can support up to 100 users and
        has normal and "SuperUser" access. It can
        also be used in Windows to secure the MS-DOS
        icon. Installed correctly, Sentry can be an
        extremely powerful security tool for your PC.
        http://dragon.acadiau.ca/~910318b/Sentry.html
        Mike Bobbitt [Mike.Bobbitt@@AcadiaU.Ca]
        -------------------CUT----------------------


        11.5 General

        Sentry is written entirely in Borland C for DOS. As of version
        2.5, Sentry contains over 2600 lines of code. Portability
        between machines is not an issue, since Sentry has been designed
        and tested on standard MS-DOS machines.

        Sentry is verified to be compatible with Windows 3.x and Windows
        95.


        12.0 Potential Threats To Security
        ==================================

        Never underestimate your users. And never be satisfied that your
        system is completely "air-tight". Users are incredibly apt at
        finding loopholes in security, and once found, these holes can
        be expoited. Because of this, I am listing below all of the
        security loopholes that I am aware of at this time.


        12.1 The Password File

        Let me once again stress again that the time stamps and user
        names are not encoded in the password file. This means that if a
        malicious user found the password file, he could edit it, and
        effectively wreak havoc on your system. Bear in mind that the
        password file is automatically hidden by Sentry, so finding it
        is not always easy. Also, most of these methods require a
        working knowledge of how Sentry operates, and that is not
        commonly available. The best source for that information would
        be from this file, which is deliberately missing some key pieces
        of "technical" information.

        If a user did manage to find the password file however, he could
        do any of the following:

        - Add/Remove an expiry date (account or password)
              This is not a serious issue for passwords, as the user
              would still have to enter their old one before being
              notified that their password has expired. An attacker
              cannot expire a password and then log in to that account.

        - Edit a username
              This would effectively lock out that user, unless they
              could guess their new user name.

        - Delete a user
              Users can be deleted, but not created.

        - Destroy a password
              Since passwords are encoded, there is no way to change a
              password to something usable. An edited password will
              likely lock that user out of their account, until the
              password is reset.

        - Change "last login" information
              Not critical, but could be used to cover an attackers
              tracks.

        - Change "number of invalid logins since last login" information
              Same as above.

        - Add/Remove restrictions on the number of invalid login attempts
              Could allow a "brute force" technique to work on an
              account password if the restriction was lifted. Also, if
              an attacker set this restriction to 1 invalid login, that
              account would be disabled if a single failed login attempt
              was made.

        It is important to know however, that a renegade user can never
        grant himself SuperUser privileges, nor can he ever view any
        users password, or attempt to effectively modify one. To perform
        any of these functions, he must be logged in as a SuperUser. In
        fact, not even SuperUsers can view passwords. Nobody can. (They
        can never be decrypted, remember?)

        In essence: KEEP YOUR PASSWORD FILE SOMEWHERE SAFE, AND
                    GUARD YOUR SUPERUSER PASSWORDS!


        12.2 Hardware Loopholes

        Although it is unlikely that a user will do this, there is a
        potential security risk to Sentry. Fortunately, this method can
        only be implemented by technical users. If a user really wants
        to get into your system, he can disassemble it, and take the
        battery out of your BIOS. This will reset your BIOS to the
        standard setup, which does not include password protection. From
        there, the user can enter your BIOS, and change the boot
        sequence from C,A to A,C. This means that your computer will
        search for a boot disk before booting from your hard drive.
        Therefore, the user can get in if he has a pre-made boot disk.
        Like I said, it's unlikely, but possible. If you want to fix up
        this back door, you can re-wire your floppy disk drive so that
        it is never used on boot up. I do not have instructions for that
        at this time, however I am looking, and will include them in
        future.

        Along the same lines, a user could replace your hard drive (the
        one containing Sentry)  with another hard-drive. This way he
        could then boot up using the new hard drive, and never have to
        worry about Sentry. Also, if he kept your hard drive on the
        system (as drive D for example), he could still access your
        data. This kind of trickery is highly improbable, but not
        impossible.

        The above two methods take more technical skill than the average
        user posesses, and should not be considered a serious threat. I
        include them simply so you can be aware such things exist. If
        you are concerned about attacks of this nature, you should
        secure your system's case to the frame (IE: make it impossible
        to open the case with a screwdriver).

        It is critical to realize that it is EXTREMELY difficult to
        repel a determined and well-organized attack. Using Sentry does
        not guarentee your computer's safety. It does however greatly
        reduce the threat of a successful attack, and more importantly,
        it can alert you to potential threats before they become a
        serious problem. Your ability to defend is much greater once you
        know you are under attack. Sentry can assist in keeping you
        informed of suspicious actions on your PC, and it is a powerful
        tool in defeating most threats.


        13.0 Troubleshooting
        ====================

        13.1 Error messages

        Below are listed all possible error messages you can get while
        running Sentry. With each is a brief description of what it
        means, probable causes, and how to fix it.

        Please be aware that ALL of these errors cause Sentry to
        lock-up. This may be an inconvenience at times, but it is done
        for security reasons (that way an attacker can't "induce" an
        error and get into the system).


        13.1.1 Error opening password file!

        This means your password file cannot be found or opened. Make
        sure your password file is at the location specified by
        "PassFile" in your Sentry.ini file. As long as it's there, you
        should have no problems.


        13.1.2 Error opening temp file!

        A temporary storage file cannot be opened. Make sure you have at
        least a little disk space left when you run Sentry.


        13.1.3 Error in creating log file!

        The file that logs all transactions to your computer cannot be
        created. Make sure you have specified a valid pathname for
        "LogFile" in the Sentry.ini file, and make sure you have some
        free space on your drive. If a log file already exists, it will
        be appended to. Otherwise it will be created.


        13.1.4 Error opening log file!

        There is a problem with the log file. Make sure that the log
        file pointed to by "LogFile" in the Sentry.ini file is not
        write-protected.


        13.1.5 Error opening Sentry.ini file!

        This means that your Sentry.ini file cannot be found. Make sure
        the Sentry.ini file is in the same directory as your Sentry.exe
        file, and that it is named correctly.


        13.1.6 Error in Sentry.ini file! [XXXXXXXX]

        Your Sentry.ini file does not follow the correct format. The
        error message should have a word in square brackets after it
        (IE: [PassFile], [PasswordExpiresIn], etc). This is the
        attribute in the Sentry.ini file that is causing the problems.
        (Sentry expects to find that attribute but doesn't). Use an
        editor to set the attribute correctly. If you are completely
        lost, restore the Sentry.ini file from you backup, or use the
        default attribute setting listed in the comments of the
        Sentry.ini file.


        13.1.7 Registration Error - Program Aborted!

        Someone (probably you) has tried unsuccessfully to change the
        registration information. Very naughty, but if you want to fix
        it, simply restore Sentry.exe from your original copy.


        13.1.8 Error in time stamps.

        This means there is a problem with the time stamps on a user's
        account. You can attempt to manually edit a user's record in the
        Sentry.pwd file, but I don't recommend this. If you don't know
        what you're doing you are more likely to cause additional
        problems than to fix the user. Otherwise, you can try restoring
        your password file from backup. If you continue to use a
        password file that is corrupt, you will probably find you are
        locked out quite frequently. It should be a top priority to fix
        the password file.


        13.1.9 Out of memory!

        When this error appears, it means that for some reason, Sentry
        didn't have enough memory to run. This is extremely rare, since
        Sentry requires very little memory. If this error occurs, try
        freeing up some memory by unloading some un-needed programs, or
        rebooting.


        13.1.10 This account has expired.

        Sorry, you're out of luck. The SuperUser(s) have set your
        account to expire, and so it has. If you ARE the SuperUser,
        silly you (you shouldn't let your own account expire!). In that
        case, you will have to restore your password file from a backup,
        and make the necessary changes to get your system running.


        13.2 Other problems

        When I run Sentry, is displays a warning saying I am using a
        newer/older version of the Sentry.ini file.

        A: You should probably get the latest version of Sentry (see
        section 11.3 for info on obtaining the latest version). Replace
        all your current files with the files you retrieve. This warning
        may not be a problem in itself, however it is not a good idea to
        use a Sentry.ini file from a different version.


        I get a warning about users being tampered with in the log file.

        A: Someone has been tampering with your users (obviously). They
        thought they could change the SuperUser access on your system,
        but really couldn't. The only side effect of this is that some
        users may appear to have SuperUser access when they don't (and
        vice-versa) when you view them from the SuperUser menu. The
        users' actual access has not changed. To remedy this situation,
        you can get the user to enter another password (this can easily
        be done by expiring their current password). As soon as the new
        password is entered, the problem will disappear.


        I can't log in at all.

        A: Make sure you are a user on the system. Make sure your
        Sentry.ini file has been set up correctly. Make sure your
        password file is in the right location.


        I can't log in as a SuperUser.

        A: Did you give yourself SuperUser access? Are you remembering
        to hold down CTRL when you hit enter?


        My password file is corrupt or deleted.

        A: Pray you kept a backup somewhere. At the very least, you
        should have the password file sent with Sentry. In that case,
        re-install, and log in as Sentry. Since Sentry is initially a
        SuperUser, you can re-create your users (don't forget to delete
        the Sentry user when you are finished!).


        I can't create a c:\Sentry directory on my drive.

        A: If you are using MS-DOS's Undelete program, it may create a
        directory called "Sentry" off of your root directory. This
        directory is hidden, and can only be seen with the "dir /a"
        command. (This only occurs if you are using the "delete sentry"
        mode). Possible fixes are to stop using "delete sentry" mode, or
        to create your Sentry directory as something else (eg:
        c:\Sentry2, c:\Secur\Sentry, etc etc).


        My password file disappeared, but Sentry still works fine!

        A: Your password file is still there, but Sentry has hidden it
        from normal view. When you type "dir" your password file will no
        longer show up. This is done to confuse and mislead any
        potential attackers. If you want to check to make sure it is
        really there, type "dir /a" and it should show up. The log file
        is protected with the same measures.


        I copied my Sentry files to another drive/directory, and now it
        says my password file is not found!

        A: This is (once again) because the password file is hidden.
        When the copy operation was performed, it didn't "find" the
        hidden file and therefore was not copied with the other files.
        Older versions of the DOS copy command can copy hidden files,
        but that function has been removed in later versions. The best
        bet to avoiding this is to re-install Sentry on the destination
        drive/directory and create your accounts from scratch. (There
        are ways to move the password file, but I won't discuss them
        here).


        15.0 Standard Disclaimer
        ========================

        Inexperienced users should take care this program, as you may
        lock yourself out of your computer!

        If you feel you want to use it, but don't feel completely
        confident, leave a "back door" for you to use. (IE: don't
        implement all of the security measures listed in "Securing Your
        Computer"), so that if you DO get locked out, you can still get
        in somehow.

        I have not included a nice simple install program on purpose. If
        you aren't familiar with the basics of DOS, then you probably
        shouldn't be installing Sentry anyway. If there is a need for an
        install program, I may include it in a future release.

        I take no responsibility for how you use this program, or any
        effects it may have on your system.

        Having said that, I would greatly appreciate any comments you
        might have about my program (either positive or negative). If
        you find any problems, or have a suggestion for making Sentry
        better, please let me know, and I'll try to put it in a future
        release. I look forward to hearing from you.

        You can contact me via e-mail at Mike.Bobbitt@@AcadiaU.Ca and I
        will reply as quickly as I can. If you do not have internet
        access, you can contact me via surface mail at:

        Michael A. Bobbitt
        P.O. Box 1336
        Wolfville, NS
        B0P 1X0


        16.0 Credits
        ============

        My thanks go out to these people:

        Mark Saarinen for the encryption algorithm.

        D.J. Houghton, Rob Coombs and Jack Hill for testing and
        advising during the design phase.

        Bret Jacobsen for finding some serious errors in the first
        release, as well as continually making suggestions for
        improvement. Bret has given invaluable assistance in the
        development of Sentry.

        ...And my wife for listening to me talk incessantly about it.
@



2.3
log
@Readme.txt V2.4 - Minor Changes
@
text
@d2 1
a2 1
                             º Sentry 2.3 º
d11 7
a17 7
            1.1 Purpose of Sentry
                1.1.1 In the Home
                1.1.2 In the Business Environment
            1.2 Features of Sentry
                1.2.1 General
                1.2.2 Expiry Dates
            1.3 Distribution of Sentry
d20 5
a24 5
            2.1 General Setup Issues
            2.2 The Initial Login
            2.3 First Priorities
            2.4 Using the SENTRY.INI file
                2.4.1 Modifying Your AUTOEXEC.BAT
d27 7
a33 7
            3.1 BIOS Password
            3.2 Boot Sequence
            3.3 Switches in CONFIG.SYS
            3.4 Passwords
            3.5 The Password File
            3.6 Placement in AUTOEXEC.BAT
            3.7 Keep a Backup
d36 2
a37 2
            4.1 The Login Procedure
            4.2 Changing Passwords
d49 2
a50 1
            5.10 Exit
d53 4
d59 2
a60 2
            7.1 General
            7.2 Setup
d77 1
d80 5
a84 5
             11.1 Encoding Algorithm
             11.2 Time Stamps
             11.3 Files
             11.4 File_id.diz
             11.5 General
d87 2
a88 2
             12.1 The Password File
             12.2 Hardware Loopholes
d91 12
a102 12
             13.1 Error messages
                  13.1.1  Error opening password file!
                  13.1.2  Error opening temp file!
                  13.1.3  Error in creating log file!
                  13.1.4  Error opening log file!
                  13.1.5  Error opening Sentry.ini file!
                  13.1.6  Error in Sentry.ini file! [XXXXXXXX]
                  13.1.7  Registration Error - Program Aborted!
                  13.1.8  Error in time stamps.
                  13.1.9  Out of memory!
                  13.1.10 This account has expired.
             13.2 Other problems
d301 1
a301 1
        2.4 Using the SENTRY.INI file
d303 1
a303 1
        Sentry can be configured to your needs by way of the SENTRY.INI
d307 1
a307 1
        The SENTRY.INI file follows a very specific format, and if you
d315 6
a320 1
        2.4.1 Modifying Your AUTOEXEC.BAT
d322 4
a325 1
        Simply add the following lines to the top of your AUTOEXEC.BAT
d329 1
a329 3
        cd \Sentry
        Sentry
        cd \
d346 1
a346 2
        cd \Sentry
        Sentry
a347 1
        cd \
d397 10
a406 10
        sentence "I'll wait for you" turns into "illw84u" (trust me).
        Mixing letters and numbers increases the security of a password,
        and passwords of this type are near impossible to guess or
        crack. Do not write your password down, especially near your
        computer. Try to memorize it if possible. Change your password,
        but not too often. People who change their passwords too often
        (less than 6 months or so) tend to write them down, which is a
        bigger risk. Don't enter your password with someone looking over
        your shoulder. If someone is in the room, block their view, or
        wait until they leave.
d717 35
a751 1
        5.10 Exit
d760 2
d775 36
a810 22
        To perform this last step, you need to use the Sentry.pif file
        included with this program. Copy this file into your Windows
        directory, and then enter Windows. From here, run the Pif Editor
        program (the icon is a little tag), and open Sentry.pif. Now
        change the "Program Filename" to c:\Sentry\Inst1\Sentry.exe and
        the "Working Directory" to c:\Sentry\Inst1. Now save the .pif
        file, and create a new program item in the group that contains
        your MS-DOS icon.

        Fill in the choices as shown below:

        Description:        MS-DOS
        Command Line:       Sentry.pif
        Working Directory:  c:\Sentry\Inst1

        At this point you can pick a new icon as well. I suggest you
        pick the regular MS-DOS icon, since you will replace your old
        one. The icon is not critical, it is used for "looks" only.

        At this point you should test out the new icon you have created
        to make sure it works ok. When you double click on the new icon,
        it shoould take you directly to Sentry. Once you have entered a
d816 10
a825 7
        users cannot use it to drop straight to DOS. Now there is one
        last step. If a user were to exit Windows, they would be at the
        DOS level, which is not what we want. Since your autoexec.bat
        file is running windows on startup, you can block people from
        exiting by forcing them to go through Sentry. You can do this by
        adding a call to Sentry after the win command in your
        autoexec.bat.
d832 1
a832 3
        cd c:\Sentry\Inst1
        Sentry
        cd c:\
d835 3
d852 10
a861 6
        information you have not saved in your Windows session, so save
        everything before using Sentry. If Sentry does lock up your
        system, you may be able to recover back to Windows by pressing
        CTRL-ALT-DELETE and closing the DOS prompt. This will still not
        allow access to DOS, but you will not lose anything you were
        working on.
d863 4
d868 47
d939 3
a941 3
        cd c:\Sentry\Inst2
        Sentry
        cd c:\prog
d943 1
a943 1
        cd c:\
d1029 3
a1031 3
        has enough security to be a fairly secure program as is, however
        if you are serious about Security, plaintext passwords are not a
        viable option.
d1280 1
a1280 1
                     * Small bugs with windowing features fixed.
d1294 25
d1407 1
d1409 1
a1409 1
        Sentry.pwd      The password file.
d1436 1
a1436 1
        (V2.3) Sentry - Security for DOS/Windows
d1452 1
a1452 1
        2.3, Sentry contains over 2600 lines of code. Portability
d1484 34
a1517 10
        force everyone's account to expire but his own. He could also
        force everyone's passwords to expire pre-maturely (not a real
        problem, since the users would simply have to enter new ones).
        He could remove any expiry dates on his account. Note that he
        could also edit usernames, effectively locking others out,
        unless they know their new login. In addition he can delete
        accounts by removing their entry in the Sentry.pwd file. Also,
        if he were to edit an encoded password, he would lock out that
        user since their password has been changed on them (the password
        would then be essentially garbage).
d1522 3
a1524 3
        any of these functions, he must already know a SuperUser's
        password. In fact, not even SuperUsers can view passwords.
        Nobody can. (They can never be decrypted, remember?)
d1533 14
a1546 13
        "back door" into Sentry. Fortunately, this method can only be
        implemented by technical users. If a user really wants to get
        into your system, he can disassemble it, and take the battery
        out of your BIOS. This will reset your BIOS to the standard
        setup, which does not include password protection. From there,
        the user can enter your BIOS, and change the boot sequence from
        C,A to A,C. This means that your computer will search for a boot
        disk before booting from your hard drive. Therefore, the user
        can get in if he has a pre-made boot disk. Like I said, it's
        unlikely, but possible. If you want to fix up this back door,
        you can re-wire your floppy disk drive so that it is never used
        on boot up. I do not have instructions for that at this time,
        however I am looking, and will include them in future.
d1558 4
a1561 1
        include them simply so you can be aware such things exist.
d1623 1
a1623 1
        file, and that your are in that directory when you run Sentry.
d1743 14
@


2.2
log
@Accompanies Sentry V2.2
@
text
@d2 1
a2 1
                             º Sentry 2.2 º
d62 10
a71 9
             10.1 Pre-Release Notes
             10.2 Sentry V1.0
             10.3 Sentry V1.1
             10.4 Sentry V1.2
             10.5 Sentry V1.3
             10.6 Sentry V1.4
             10.7 Sentry V2.0
             10.8 Sentry V2.1
             10.9 Sentry V2.2
a95 1
                  13.1.11 Internal Window Error.
a231 4
        Please note that there are no "quick install" instructions
        provided. This is because all the information in this section is
        considered critical and should be read over thoroughly before
        attempting to run Sentry.
a232 1

d315 1
a315 1
        cd c:\Sentry
d317 1
a317 1
        cd c:\
d328 12
d1155 20
d1269 1
d1291 1
a1291 1
        (V2.2) Sentry - Security for DOS/Windows
d1307 1
a1307 1
        2.2, Sentry contains over 2500 lines of code. Portability
d1311 3
d1505 10
@


1.2
log
@Readme file for Sentry V2.0
@
text
@d1 4
a4 4
                             ________________
                            <|  Sentry 2.0  |>
                             ~~~~~~~~~~~~~~~~
                             Michael A. Bobbitt
d6 1
a6 1
                http://dragon.acadiau.ca/~910318b/Sentry.html
d17 1
d21 4
a24 2
            2.2 Using the SENTRY.INI file
                2.0.2 Modifying Your AUTOEXEC.BAT
d54 2
d69 2
d85 11
d103 1
a104 1

d207 15
d252 3
d262 11
a272 9
        "Sentry". (The case is important, "sentry" or "SENTRY" will not
        work!) The Sentry account has SuperUser access, meaning you can
        create and delete accounts while logged in as Sentry. To log in
        as a superuser, enter Sentry for a login, and instead of
        pressing enter, hold down the CONTROL key and press enter. This
        tells the Sentry program that you want to log in as a SuperUser.
        Then enter your password normally, and instead of dropping to
        DOS, you will go to the SuperUser menu. (See the section below
        on "The SuperUser Menu" for more information).
d281 3
d300 1
a300 1
        2.2 Using the SENTRY.INI file
d314 1
a314 1
        2.0.2 Modifying Your AUTOEXEC.BAT
d407 1
d414 1
d445 4
d557 1
a557 1
        5.5 Change Account Exipry Date
d792 2
d802 3
d889 9
a897 1
        security program, and I'd appreciate it very much.
d905 1
a905 9
        good idea.

        Please feel free to distribute the ShareWare version of Sentry
        freely.

        DO NOT distribute any registered versions whatsoever. (By
        distributing a registered version, you are giving out copies of
        a specific encoding scheme, which can be used against the
        registered user).
d922 2
a923 1
              - Notices about any potential security risks.
d925 2
a926 2
        As well as the ability to request specific features in future
        versions of Sentry.
d942 2
a943 1
                    unsuccessful. The general idea for Sentry is formed.
d978 2
a979 1
                       immediately.
d981 1
d997 1
d1019 1
d1035 1
d1044 3
a1046 3
                     * Invalid length messages (both to the screen and
                       log file) are user-definable in the Sentry.ini
                       file.
d1061 1
a1061 1
                     * The log file is re-organized to be more
d1090 58
a1175 1
        ... and so on...
d1236 1
d1238 3
a1240 1
        Sentry.pif      The Sentry .pif file for Windows.
d1242 2
a1243 3
        Readme.com      Displays this file.
        Order.frm       The order form.
        File_id.diz     Short description file.
d1263 1
a1263 1
        (V2.0) Sentry - Security for DOS/Windows
d1279 1
a1279 1
        2.0, Sentry contails over 2350 lines of code. Portability
d1359 9
d1369 1
d1381 2
a1382 2
        for security reasons (that way a user can't "induce" an error
        and get into the system).
d1385 1
a1385 1
        Error opening password file!
d1393 1
a1393 1
        Error opening temp file!
d1395 2
a1396 2
        A temporary storage file cannot be opened. Make sure you have a
        little disk space left when you run Sentry.
d1399 1
a1399 1
        Error in creating log file!
d1408 1
a1408 1
        Error opening log file!
d1410 3
a1412 2
        There is a problem with the log file. Make sure that you have
        some free disk space on your disk when you run Sentry.
d1415 1
a1415 1
        Error opening Sentry.ini file!
d1422 1
a1422 1
        Error in Sentry.ini file! [XXXXXXXX]
d1435 1
a1435 1
        Registration Error - Program Aborted!
d1442 1
a1442 1
        Error in time stamps.
d1445 8
a1452 5
        account. If you are going to attempt to manually fix the
        password file, bear in mind that there should be 3 time stamps
        per user, each in standard UNIX format. Otherwise, you can try
        deleting and re-creating the afflicted user (this may cause more
        trouble if there are serious problems with your password file).
d1455 1
a1455 1
        Out of memory!
d1460 2
a1461 1
        freeing up some memory by unloading some un-needed programs.
d1464 1
a1464 1
        This account has expired.
d1534 2
a1535 2
        Inexperienced users should probably avoid using this program, as
        you may lock yourself out of your computer!
d1539 3
a1541 2
        implement all of the security measures listed above, so that if
        you DO get locked out, you can still get in somehow).
d1553 1
a1553 1
        you find any bugs, or have a suggestion for making Sentry
d1555 1
a1555 1
        release.
d1572 2
d1578 3
a1580 1
        release, as well as making suggestions for improvement.
d1582 1
a1582 1
        And my wife for listening to me talk incessantly about it.
@


1.1
log
@Initial revision
@
text
@d2 1
a2 1
                            <|  Sentry 1.5  |>
d37 10
a46 9
            5.1 Create User
            5.2 Delete User
            5.3 View Users
            5.4 Toggle SuperUser Status
            5.5 Change Account Exipry Date
            5.6 Change Password Expiry Date
            5.7 View Log File
            5.8 Change Account Password
            5.9 Exit
d57 7
d199 4
d204 1
d404 3
a406 1
        many.
d438 1
d481 9
a489 5
        of the user's login name. You can use the PAGE UP and PAGE DOWN
        keys to scroll forward and back if there are multiple pages of
        users. Arrows ( and ) will be present if there are additional
        pages above and/or below. The ESCAPE key will exit back to the
        main menu.
d518 6
d604 50
a653 1
        5.9 Exit
d655 1
a655 1
        Simply returns you to the DOS prompt. This is the same as
d835 4
d842 7
a848 2
        Sentry before you commit to purchasing it. Please feel free to
        distribute the ShareWare version of Sentry freely.
d882 1
d886 2
d899 5
a903 1
        20 July 95 - Sentry V1.0 (Shareware) is released.
d905 3
a907 2
        27 July 95 - Sentry V1.1 Released. V1.1 fixes some problems in
                     V1.0, and has these additions:
d909 8
d926 1
a926 1
        29 July 95 - Sentry V1.2 Released. Additions are:
d928 5
d941 3
a943 1
        01 Aug 95  - Sentry V1.3 Released. Additions are:
d945 3
d962 6
a967 1
        08 Aug 95  - Sentry V1.4 Released. Additions are:
d977 1
a977 1
        10 Aug 95 - Sentry V1.5 Released. Additions are:
d979 6
d1024 6
d1145 1
a1145 1
        (V1.5) Sentry - Security for DOS/Windows
d1161 1
a1161 1
        1.5, Sentry contails over 2100 lines of code. Portability
d1444 1
a1444 1
        And my wife for lisening to me talk incessantly about it.
@
