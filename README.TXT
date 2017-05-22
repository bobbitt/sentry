













                                S e n t r y
                                ===========
                                    V6.5

                             Instruction Manual

                           Copyright (C) 1995-1999
                           Cipher Logic Canada Inc.

                           info@cipherlogic.on.ca

                        http://www.cipherlogic.on.ca




                                S e n t r y
                                ===========
                             Table of Contents

        1.0 Introduction
            1.1  Purpose of Sentry
                 1.1.1 In the Home
                 1.1.2 In a Business Environment
                 1.1.3 In an Educational Environment
                 1.1.4 In Government Institutions
                 1.1.5 General
            1.2  Features of Sentry
                 1.2.1 General
                 1.2.2 Expiry Dates
                 1.2.3 Windows
                 1.2.4 File Protection
                 1.2.5 Modify Shell Commands
                 1.2.6 Virus Protection
                 1.2.7 Online Help
                 1.2.8 Screen Saver
                 1.2.9 Language Support
            1.3  Distribution of Sentry

        2.0 Setup
            2.1  Installing Sentry
                 2.1.1 Windows Install
                 2.1.2 DOS Based Install
            2.2  The Initial Login
            2.3  First Priorities
            2.4  Using the Initialization Settings
            2.5  Uninstalling Sentry
                 2.5.1 Windows Un-Install
                 2.5.2 DOS Based Un-Install
            2.6  Installing Sentry on Multiple Machines

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
            5.1  User Maintenance Menu
                 5.1.1  Create User
                 5.1.2  Delete User
                 5.1.3  View Users
                 5.1.4  Toggle SuperUser Status
                 5.1.5  Change Account Expiry Date
                 5.1.6  Change Password Expiry Date
                 5.1.7  Change Account Password
                 5.1.8  Assign Max Invalid Logins
                 5.1.9  Return to SuperUser Menu
            5.2  Log File Maintenance Menu
                 5.2.1  View Log File
                 5.2.2  View Backup Log File
                 5.2.3  Move Log File to Backup
                 5.2.4  Return to SuperUser Menu
            5.3  System Maintenance Menu
                 5.3.1  Edit Initialization Settings
                 5.3.2  Send a Message to a User
                 5.3.3  Protect a File
                 5.3.4  Export Initialization Settings
                 5.3.5  Import Initialization Settings
                 5.3.6  Security Audit
                 5.3.7  Modify Shell Commands
                 5.3.8  Return to SuperUser Menu
            5.4  Sentry DOS Shell
            5.5  About Sentry
            5.6  Exit

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
            7.6  Upgrading a Protected File

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
             10.39 Last Login Pause
             10.40 Secure Deletion
             10.41 View Highlighting
             10.42 View Highlighting Colour
             10.43 Disable CTRL-C
             10.44 Password Echo Count

        11.0 Technical Notes
             11.1  Encoding Algorithm
             11.2  SuperUser Access
             11.3  Packing List
             11.4  File_id.diz
             11.5  Date Conversion
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
                   13.1.23 The Initialization Settings Are Old!
                   13.1.24 The Initialization Settings Are New!
                   13.1.25 Executable Intrgrity Error!
                   13.1.26 Error Opening String File!
             13.2  Other problems

        14.0 Standard Disclaimer

        15.0 Contact Information

        16.0 About the Author

        17.0 Credits

                           ========================






                                S e n t r y
                                ===========
                     Security for the Home and Business





        1.0 Introduction
        ================

        Currently, almost all fields of computer security are growing
        and advancing, with a few notable exceptions. Networks, servers
        and public access systems are all tightening their access to
        avoid potential problems. But what about the PC? Is the
        information contained on these any less valuable? Often times
        not, yet adequate security programs do not exist for PC's. In my
        search for security, I discovered that PC's were virtually
        ignored, and those programs that did exist were weak and faulty.
        Faced with this situation, I decided to write my own security
        program from scratch, incorporating the tightest security
        measures possible, while allowing flexible, easy use.

        Since Sentry is invoked before any networks are detected, and
        before "high level" operating systems such as Windows
        initialize, it provides absolute security for these items.
        "Networked" security solutions are often faulty since
        experienced users can gain access to the local network before
        the security measures are in place.


        1.1 Purpose of Sentry

        Sentry is meant for one basic purpose only: to keep unwanted
        people out of "private" information. It is flexible enough that
        this single purpose can be used in many different ways, for many
        different reasons. Here are just a few.

        1.1.1 In the Home

        Most people have something on their home PC that they consider
        to be "sensitive". Maybe it's a private letter, maybe it's
        copies of e-mail, or maybe it's financial information. Quite
        possibly, you just want a way to keep track of who is using your
        system. Sentry has the solution for all of these problems, by
        restricting access and logging all attempts to use the system.

        Alternatively, sometimes you just want to keep people out,
        period. It could be your nosy room mate or your little brother.
        In any case, Sentry will keep them out, while letting a select
        group of people in.


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

        For businesses that work in groups, Sentry is perfect for
        keeping track of who used the PC's and when. Supervisors could
        have SuperUser access on all PC's in their group, allowing them
        to manage and control access as required. Also, the log that
        Sentry keeps could be a valuable tool in determining who was
        doing what, and when.

        Once a member leaves the project, simply expire or delete their
        account to avoid any unauthorized access.


        1.1.3 In an Educational Environment

        Schools and educational institutes will find Sentry very useful
        for limiting access to certain terminals. If, for example, only
        a select group of people (staff, administrators, or a certain
        class) should have access to specific PC's, simply give each
        person an account. Anyone without an account cannot log in.
        Sentry will also help track usage, attempted break-ins, and any
        other suspicious activity.

        Sentry also allows you to disable or "hide" undesirable DOS
        commands. For example, using Sentry, you can disable the DEL
        command, blocking students from destroying files and data.
        Alternatively, you can rename or hide the DEL command to
        something like ZAP, allowing you use of the command for
        administrative purposes, but blocking others.

        Often school terminals are left unattended, with nothing to stop
        a student from "poking around." Sentry can also act as
        protection from the prying eyes of the student body.


        1.1.4 In Government Institutions

        It is sometimes necessary to restrict access to a single program
        on a computer. Quite possibly, there are several people with
        different clearances who use the same machine. Some programs may
        perform actions, or contain data, that should not be accessible
        to all users. To rectify the problem, Sentry can protect the
        sensitive program, requiring a username and password each time
        it is run. The "protected" version of the program has all of the
        features of Sentry, including 2 levels of access, expiration
        dates, self-defence against attacks and a mini-message system.


        1.1.5 General

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


        1.2.5 Modify Shell Commands

        Another useful feature of Sentry is the ability to modify the
        DOS command interpreter. This can be used to remove harmful
        commands like DEL, or to "hide" commands such as COPY under
        another name. For organizations that have public access to their
        PC's this feature is a must.


        1.2.6 Virus Protection

        Sentry also offers protection against viruses and hackers by
        performing a self-check before it begins normal execution. If
        Sentry's executable has been modified or added to in any way,
        Sentry will know, and will not execute further. Since many
        viruses work by attaching themselves to executable files, Sentry
        is very useful for detecting their presence on your system.

        In addition, this form of protection stops hackers from
        potentially modifying the way Sentry runs. For example, a hacker
        can no longer "re-program" Sentry to perform illegal operations,
        or give unauthorized access.


        1.2.7 Online Help

        Context sensitive help is available at any time simply by
        pressing the F1 key.


        1.2.8 Screen Saver

        Sentry has a built-in screen saver, to enhance security and
        to prevent burn-in. This screen saver is automatically
        activated after a user configurable period of time, or it can
        be turned on manually by pressing the F2 key.

        It is useful at times to force the screen saver to come on
        before the designated time has expired, such as when you're
        forced to leave your workstation unexpectedly, or when
        you don't wish the information on the screen to be visible.

        The built-in screen saver is only active when Sentry is running.


        1.2.9 Language Support

        Sentry has been designed to support multiple languages, and to
        allow the user to switch between languages at the touch of a key.
        Pressing the F3 key at any point will display a menu with all
        of the available language choices. Once a new language is
        selected, it takes effect immediately.

        Currently supported languages are:

         - English
         - Spanish

        If you are willing to spend the time to translate Sentry into
        an additional language, please contact me, and hopefully we
        can work out a deal.


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

        The installation of Sentry is very straightforward, however for
        those who are new to software installation, instructions are
        provided below. There are currently two methods which are
        available for installation. Both methods perform the same
        actions, and allow the user to work in the environment they are
        most comfortable with.


        2.1.1 Windows Install

        The Windows based install is the fastest and easiest route. To
        follow this path, simply run SETUP.EXE. This will initiate the
        setup program.

        After the splash screen appears, you will presented with a
        welcome screen. Press the "Next" button to continue.

        The next screen contains the license agreement. Be sure you have
        read and fully understand it. By using the software, you agree
        to the terms of the license. Press "Yes" if you agree with the
        license.

        If you are running the registered version, you will be prompted
        for your registration information at this point. Use the
        information that was sent to you with your registered copy of
        Sentry. Press "Next" to continue.

        You will now be prompted to enter a username and password for
        the primary SuperUser. Additional SuperUser accounts can be
        created once the installation is complete. Once the information
        is entered, press the "Next" button.

        You will be asked if you would like Sentry to modify your system
        files. Doing so makes Sentry execute every time your machine
        boots up. If you answer "No" to this question, Sentry will not
        be able to protect your machine from unauthorized access. Press
        "Yes" if you want to activate Sentry.

        The next screen prompts you for the installation location. This
        is where Sentry's files will live. The default is C:\Program
        Files\Sentry, however you can change it to any directory you
        like. Once you have selected the directory, press the "Next"
        button.

        Setup will now copy Sentry's files into the location you just
        specified.

        At this point, you will be notified that Sentry will run a
        custom install routine. Press "OK." For new users, this custom
        routine will finish automatically. Upgrading users may be
        required to answer some questions. If the window that the custom
        routine runs in doesn't disappear, close it once the "****
        FINISHED ****" message appears.

        Once the custom routine finishes, installation is complete.
        Press the "Finish" button to exit the installation process.


        2.1.2 DOS Based Install

        This is the original install method, and is generally less
        favoured than the Windows Install method described above.

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

        If this is the first time you've installed Sentry, or if you're
        installing from scratch, you will be asked for some registration
        information (registered versions only). This information will be
        located on your initial letter, or upgrade notice, as
        applicable.

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

        Your first login to Sentry will be as a SuperUser. You will use
        the username and password you provided during the install
        process to log in. This will enable you to begin customizing
        your installation.

        As soon as you are ready, run Sentry from the DOS prompt (by
        typing "SENTRY" while in the proper directory). If an error
        message appears, consult section 13. Performing a check prior to
        the first reboot is always wise. It will notify you of any
        problems before the opportunity to lock yourself out has passed.

        To log in to the SuperUser menu, hold down the CTRL key when
        pressing ENTER, after you have typed in the username. If you do
        not wish to enter the SuperUser menu, simply press ENTER. Both
        login names and passwords are case sensitive by default, so
        remember any capital letters. You can turn off case sensitivity
        for logins by editing initialization settings, but the password
        will always be case sensitive.

        If you chose to enter the SuperUser menu, Sentry will not exit,
        but it will now bring up a list of options.

        See the section below on "The SuperUser Menu" for more
        information.


        2.3 First Priorities

        Once you are comfortable with using Sentry, you can create the
        other users of your system, and define their starting passwords,
        expiry dates and access rights. See the section below on "The
        SuperUser Menu" for more information.


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

        Should the need ever arise to remove Sentry from your system,
        there are two methods of doing so available to you.


        2.5.1 Windows Un-Install

        The Windows based un-install option for Sentry is simple. Under
        the Control Panel, select "Add/Remove Programs" and a window
        will appear with a list of installed software. You can select
        Sentry from this list, and then click on the Add/Remove button.
        If you confirm your selection, Sentry will be un-installed from
        your hard-drive.

        At this point, the Windows based un-install does not remove the
        reference to Sentry from your autoexec.bat file. If desired,
        this can be done manually.


        2.5.2 DOS Based Un-Install

        As with the DOS based install, the un-install method is less
        frequntly used, but is just as capable of removing Sentry from
        your system.

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


        2.6 Installing Sentry on Multiple Machines

        In many cases it is desirable to install Sentry on multiple
        machines, to provide security to an entire computer lab or
        working area. Often, the system administrator will want specific
        accounts or initialization settings on each machine. To avoid
        having to set these up individually, the process outlined below
        can be followed.

        1. Install Sentry using your favourite method (listed above).
        When prompted, enter "A:\" for the install path.

        2. Enter the locations for the log, backup log and message
        files. If these locations are to be the same on each machine,
        then enter that location here (eg: C:\Sentry.log, etc).

        3. Do not update your system files, and do not choose to use
        Sentry with Windows or Windows 95.

        4. Switch to the floppy drive (Eg: "A:"), and run Sentry.exe.
        Log in as Sentry, and set up the accounts and initialization
        settings you want to have on all machines.

        5. Copy the Install.exe program to A:\. You will likely have to
        copy it from the original disk or zip file, as the install
        program deletes itself after running. (Eg: "COPY c:INSTALL.EXE
        A:\"). Write protect the disk so that the install program will
        not be deleted with every installation.

        6. Now take the disk to a machine you wish to install Sentry on.

        7. Switch to the floppy drive (Eg: "A:") and run the install
        program again. Enter the path you wish to install to (Eg:
        "C:\SENTRY"). Do not overwrite the default settings, but do
        update the startup files. Install Sentry for use with Windows or
        Windows 95 if desired.

        8. Switch to the hard disk (Eg: "C:") and run Sentry. Update the
        accounts and initialization settings which are specific to that
        machine.

        9. Repeat steps 6-8 for each machine required.

        Once these steps are complete, every machine that Sentry has
        been installed on will have the defaults set up in step 5. This
        can save a considerable amount of time when installing on a
        large number of machines.


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
        will be displayed. Pressing 'd' will delete that message, and
        'r' will reply to it. After replying, you will be asked if you
        want to delete the original message. Each message is displayed
        individually.

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

            1.  User Maintenance Menu
            2.  Log File Maintenance Menu
            3.  System Maintenance Menu
            4.  Sentry DOS Shell
            5.  About Sentry
            6.  Exit

        Hotkeys can be used to jump to any sub-menu at any time. The
        keys are:

        U - User Manitenance Menu
        L - Log File Maintenance Menu
        S - System Maintenance Menu

        Note that to avoid conflicts with other hotkeys, the menu
        hotkeys are all upper case.

        Each option on the main SuperUser menu is described below.


        5.1  User Maintenance Menu

        The User Maintenance Menu contains all actions that affect
        users. The following options can be accessed through the User
        Maintenance Menu:

            1.  Create User
            2.  Delete User
            3.  View Users
            4.  Toggle SuperUser Status
            5.  Change Account Expiry Date
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
        multiple pages of users.

        Some information on this screen may be highlighted, if the View
        Highlighting option is turned on. Below is a list of information
        that is automatically hightlighted by Sentry:

        - Superusers         - Accounts that have not been used recently
        - Expired Accounts   - Expired Passwords
        - Exceeded maximum invalid logins

        At any time while viewing the userlist, you may press the DEL
        key to delete the current user, or press the INS key to insert a
        new user at the end of the list.

        Arrows will be present if there are additional pages
        above/below. The ESC key will exit back to the main menu.


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


        5.1.5  Change Account Expiry Date

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
        will expire. The year must be entered as 4 digits (IE: 1998). If
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
        (IE: 1998). If you enter 'N' at the year prompt, no expiry date
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


        5.2  Log File Maintenance Menu

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


        5.3  System Maintenance Menu

        The System Maintenance Menu contains functions which allow the
        SuperUser to perform special functions or system related tasks.
        The following options can be accessed through the System
        Maintenance Menu:

            1. Edit Initialization Settings
            2. Send a Message to a User
            3. Protect a File
            4. Export Initialization Settings
            5. Security Audit
            6. Modify Shell Commands
            7. Return to SuperUser Menu

        Each option is described below.


        5.3.1  Edit Initialization Settings

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

        Any changes take place immediately.

        See section 10 for details on individual settings.


        5.3.2  Send a Message to a User

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

        The user then has the option to delete or reply to the message.
        If they do not delete the message, they will also see it on
        their next login.

        NOTE: Messages are displayed before any login information, so
        you can send messages to users that are locked out. That way, if
        you wish to send an explanation, you can.


        5.3.3  Protect a File

        This option allows you to protect executable files (.EXE, .COM
        and .BAT). Please note: once a file is protected, it can *never*
        be undone! That means if you don't have a backup, your file will
        always be protected! I highly recommend making a backup and
        storing it on a floppy, "Just In Case."

        When this option is selected, you will be presented with a list
        of files available to protect in the current directory. If there
        are subdirectories, they will be shown as well. If the file you
        want to protect is not in the current directory, simply navigate
        through the drive until you find it. You can enter a
        subdirectory by selecting it and hitting enter. Likewise, you
        can "back up" to the parent directory by selecting the "..\" and
        hitting enter. To change drives, simply press 'D' followed by
        the new drive letter.

        Once you have found the file you want to protect, simply select
        it and hit enter. Sentry will processes that file, and
        "protects" it. Protection means that the next time that file is
        run, Sentry will execute. If the user enters a valid login and
        password, then the original file executes. If not, then the file
        is not executed.

        This is useful for protecting individual files. After all, if a
        person successfully logs into your computer, they have free
        access to anything there. This will allow you to tighten up
        access to individual files.

        The current method of protection does not work with all files.
        That is to say, I have tested it on some files that do not run
        correctly once protected. (It seems to be memory or video
        conflicts). Currently, a protected file has about 100k less
        memory available to it than if it was run normally. These issues
        are "on the list" for research.

        See section 7 for specific details on protecting files.


        5.3.4  Export Initialization Settings

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
        plan to import them right away into a new version (dumping your
        settings without using them can cause a slight security risk).


        5.3.5  Import Initialization Settings

        Importing your initialization settings can be useful for several
        purposes:

         - Restoring a corrupted account structure from backup
         - Quickly installing the same configuration on multiple machines

        Obviously, you must export settings before you can import them.
        (See the previous section)

        When this option is selected, you will be presented with a file
        list. Sentry's settings are always saved in a file called
        "settings," which will be shown on the list, if in the current
        directory. If there are subdirectories, they will be shown as
        well. If the settings file is not in the current directory,
        simply navigate through the drive until you find it. You can
        enter a subdirectory by selecting it and hitting enter.
        Likewise, you can "back up" to the parent directory by
        selecting the "..\" and hitting enter. To change drives, simply
        press 'D' followed by the new drive letter.

        Once you have located and selected your settings file, Sentry
        will proceed to import it, discarding it's current setup in
        favour of the new one. Once the import is complete, Sentry
        will exit, preventing a mix of the old and new settings from
        causing problems.

        It is often useful to import settings when performing a mass
        deployment of Sentry. To accomplish this, simply set up a
        single machine with the settings you require. Next, export
        those settings (see above) and copy the "settings" file
        to a floppy disk.

        If your are installing from scratch or upgrading, simply copy
        the settings file into the target directory before running
        install.exe. The new settings will be automatically sensed
        and used.

        If you are re-configuring existing installations of Sentry,
        all you need to do is run the import settings command, and
        locate the master settings file on diskette. The settings
        will be read in, and your installation of Sentry will be
        updated to match the master.


        5.3.6  Security Audit

        This is one of the more powerful options in Sentry. Selecting
        this option will cause Sentry to automatically search for
        weaknesses in your setup. The audit searches in three main
        areas:

            - System
            - Initialization Settings
            - Account Structure

        Upon entering the audit screen, a list of all possible items
        which can be audited is displayed. This allows for cases where
        some items need not be audited. To select the item(s) to audit,
        simply highlight the item in question and press the space bar.
        An [X] denotes an item to be audited, where an [ ] denotes that
        the item will not be checked. Once all the desired items have
        been selected, pressing ENTER will begin the audit.

        As each of the selected items is tested, the user will be
        informed of Sentry's findings. If a section has no weaknesses
        detected, then an "Ok" will appear. Otherwise, Sentry will
        describe the weakness, and ask if you want to fix it. Pressing
        'y' will either fix the problem automatically, or prompt you to
        input a new setting, depending on the situation.

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
            - secure deletion is off

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


        5.3.7  Modify Shell Commands

        This option allows the SuperUser to control the commands
        are available to users at the DOS prompt. This option can be
        extremely valuable when implementing a total security plan.

        To begin with, the SuperUser is prompted for the location of the
        command interpreter. This is usually located in the root
        directory (C:\), or in C:\DOS for regular DOS installations, or
        in C:\windows for Windows 95 users. Sentry will use the location
        held in the COMSPEC environment variable as the default, making
        it easier for you to find the right file.

        Once you enter the location of your command interpreter, Sentry
        scans it in an attempt to discover what commands it controls. If
        Sentry cannot find any valid commands, it will inform the
        SuperUser, and nothing will be modified.

        If Sentry can locate some commands, they will be displayed in a
        menu format. At this point, the user may disable or edit any of
        the commands shown.

        NOTE: It is *strongly* advised that a bookdisk is made before
        attempting any changes to your command interpreter. Although
        Sentry has been tested successfully on various command
        interperters (such as DOS 6.22, Windows 95 an Noron DOS), it may
        act in an inconsistent manner when faced with an unknown
        format.

        To disable a command, simply hit 'd' once. Hitting 'd' again
        will re-enable the command. To edit a command, simply hit 'e'
        and you will be prompted for the new command.

        ANOTHER NOTE: Is is also very advisable to make the new command
        the same length as the old command. Changing the length of a
        command can also have unpredicatable results, and is less likely
        to work.

        On the menu, commands that have been disabled are designated
        with a 'X', while commands that have been edied are designated
        with a '*', and commands that have not been modified are
        designated with a '-'.

        Once all required changes have been made, simply press enter.
        All changes will be summarized, to make sure no mistakes have
        been made. At this point, the SuperUser should ensure that all
        changes look ok, and then either accept or reject them.

        If the changes are accepted, Sentry runs the modified command
        interpreter as a test, before replacing the real interpreter.
        This means that if there are any problems, you can discard the
        changes, and start again.

        When the new shell runs, make sure you test it thoroughly. Don't
        perform any "large" operations or run any major programs, as
        that may upset the process. Once you are satisfied, type "EXIT"
        to return to Sentry, where you will be asked if there were any
        problems.

        If you answer 'N' to this prompt, your command interperter will
        be replaced with the new one, effectively making the changes
        permanent. Any other input will discard the changes.

        ONE FINAL NOTE: It is advisable to keep a "clean" copy of your
        COMMAND.COM somewhere safe, as you may want it later. Many of
        the changes you make throguh Sentry can also be undone through
        Sentry, however it is much safer to simply restore your original
        from backup. The more times you modify the same command
        interpreter, the greater the chance of something going wrong.


        5.3.8  Return to SuperUser Menu

        This option simply returns you to the SuperUser menu. It is the
        same as hitting the ESC key.


        5.4  Sentry DOS Shell

        Selecting this option temporarily drops the SuperUser to a DOS
        shell where they can execute any normal DOS commands. This shell
        has limited memory and environment space, and should only be
        used for simple file maintenance. Do not attempt to run any
        large or complicated files while in the DOS shell.

        Type "EXIT" to return to the SuperUser menu.


        5.5  About Sentry


        This option simply shows some "nice to know" information about
        Sentry.


        5.6  Exit

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
        SuperUser menu. Sentry will display a list of valid files it can
        protect. Sentry can only protect executable files (IE: it ends
        with .EXE, .COM or .BAT). Batch files are automatically
        converted into .EXE files. Once you have selected the file you
        wish to protect, Sentry will ask if the program is a Windows
        based program, or a DOS based program. Simply press 'w' for
        Windows, or 'd' for DOS. (A Windows based program is one that
        runs in the Windows environment. A DOS based program is one that
        is usually run from the DOS prompt.)

        Sentry cannot protected Windows based programs in Windows 3.x,
        however it can protect all Windows programs (16 and 32 bit) in
        Windows 95.

        Sentry will then proceed to protect the file. When it is
        finished, you will be returned to the list of files. Your file
        is now protected!

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

        Each of the instances shown above contain a complete copy of
        Sentry. Next simply modify the account structure of each
        instance to match the template. That is, the Private instance
        would contain only the SuperUser(s), the Public may contain all
        users, and the Semi-Public would contain the SuperUser(s) plus
        some users. Templates can be created to suit the needs of your
        individual site.

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
        run the protected file. If the protected file was designated as
        a DOS program, when execution of the protected file is complete,
        the user will be returned to whatever they were doing prior to
        execution (IE: the DOS prompt, etc).

        Windows based programs act a little differently. Since Sentry
        cannot detect when a Windows based program is finished
        executing, Sentry needs a cue from the user to tell it the
        program has terminated. A protected file that has been
        designated as a "Windows Bsed Program" during setup will execute
        as normal, but instead of terminating, Sentry will stay active
        (usually in a DOS box) and await user input.

        In these cases, it is important to make sure the protected file
        has completely finished executing before pressing a key in the
        Sentry DOS box. Telling Sentry the program has finished
        executing when it hasn't will cause a "Sharing violation" error,
        and could lead to a compromise in your system security. (IE: A
        skilled user could execute the protected file without an
        account). For this reason, you should be absolutely certain the
        program has terminated before allowing Sentry to continue with
        the "clean-up" it needs to do.

        If you encounter difficulties with running a Windows program
        protected by Sentry, check Section 13 for troubleshooting tips.

        Command line arguments are passed to protected files in the same
        manner as usual. To run the file FORMAT with the argument A:, it
        would look like this:

        format a:

        which is identical to the usual way of passing command line
        arguments.


        7.6 Upgrading a Protected File

        Although it is not necessary to do so every time you upgrade
        your primary Sentry installation, protected files can also be
        upgraded with each new level of Sentry, if you wish.

        Caution:  Unlike upgrading Sentry, Initialization Settings can
                  NOT be exported from Protected Files.

        As with initial file protection (see 7.3 above), the account
        structure will be copied from the version of Sentry which you
        use to protect the file.  The SuperUser will then need to modify
        initialization settings and users to obtain the desired setup.

        Upgrading may be used to "copy over" the initialization settings
        and account structure of a protected file, should you want to
        start again, or make large changes to access levels.

        Upgrading can also turn a conventional DOS based protected file
        into a Windows based protected file, if required.


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

              - The additional utility SDEL, which allows you to delete
                any file in a secure manner.

              - A laser printed user's manual (essentially this file,
                with a few changes in format and content).

              - Unlimited install support to get you up and running
                quickly.

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
        Sentry with your account information).


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
        The size is given in number of kilobytes (1024 bytes).

        0 = Never backup the log file.

        Default: 20


        10.9 Key to Change Password

        Sets the "key" to enter as a password to change passwords.

        Enter '*' to disallow password changes by users.

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

        0 = Never activate screen saver.

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

        This allows you to choose between normal windows, and
        "exploding" windows. This is strictly a visual setting, and has
        no effect on security.

        (1=Normal Windowed Mode, 2=Exploding Windowed Mode)

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


        10.39 Last Login Pause

        This setting determines how long the last login information is
        displayed on screen before the screen is cleared. A value of 0
        means that there is no pause, and the last login information is
        not cleared from the screen. Any other value is the number of
        seconds to display the last login info.

        Default: 0


        10.40 Secure Deletion

        This option allows the SuperUser to turn secure deletion on or
        off. With this option on, any files deleted by Sentry are not
        recoverable.

        (0=Normal Deletion, 1=Secure Deletion)

        Default: 1


        10.41 View Highlighting

        The setting controls how user information is displayed on the
        SuperUser menu. With view highlighting on, the following items are
        highlighted, making them easier to pick out:

        - Superusers         - Accounts that have not been used recently
        - Expired Accounts   - Expired Passwords
        - Exceeded maximum invalid logins

        As this options causes some slowdown, you may wish to disable it.
        (0=View Highlighting off, 1=View Highlighting on)

        Default: 1


        10.42 View Highlighting Colour

        You can set View to the value of the colour you wish
        normal text to have as a background. Colour values are shown in the
        chart below.

        COLOURS:
        0 Black 4 Red        8 Dark Gray    12 Light Red
        1 Blue  5 Magenta    9 Light Blue   13 Light Magenta
        2 Green 6 Brown      10 Light Green 14 Yellow
        3 Cyan  7 Light Gray 11 Light Cyan  15 White

        Default: 12


        10.43 Disable CTRL-C

        This option allows you to disable CTRL-C, CTRL-BREAK, and
        CTRL-ALT-DELETE. You may wish to do this as using these key
        sequences can at times allow the user to bypass security
        elements. This setting should only be set of copies of Sentry
        that run during bootup. Enabling this feature uses less than 1k
        of conventional memory, and remains active even after Sentry has
        finished execution.

        Please Note: Using this option may cause unusual memory usage in
        Windows 95 or Windows 3.x. If you notice that your memory usage
        is high, disable this option.

        (0=Enable CRTL-C, 1=Disable CTRL-C)

        Default: 1


        10.44 Password Echo Count

        This allows you to set the number of characters echoed to the screen
        when entering your password. This can be useful to prevent "shoulder
        surfing," as the actual number of keypresses in your password is
        being disguised.

        Default: 1


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
        encrypted version. As a result, the maximum search time may be
        much greater.


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


        11.3  Packing List

        The following files are included with this release of Sentry:

        Sentry.exe      This is the executable program.
        Install.exe     The installation program.
        Sdel.exe        A utility allowing secure deletion of files.*
        Cbreak.sys      Used to disable CTRL-C.
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
        Sentry.url      An Internet Shortcut to Sentry's Home Page.
        Sentry.w95      The Sentry .pif file for Windows 95.
        Whatsnew.txt    A short description of modifications to the
                        latest version.

        If you do not have all of these files, Sentry may not work for
        you. You can pick up a complete copy of Sentry (and updates as
        they become available) at:

           http://www.cipherlogic.on.ca

        * SDEL.EXE is included only in registered versions.


        11.4  File_id.diz

        The actual contents of the file_id.diz file are shown below. If
        any modification has been made to the original file, please
        re-create it from the following section.

        NOTE: this is primarily for SysOps of BBS's. Single users can
        delete the file_id.diz if they wish. (However, please make sure
        that all files are present if you distribute the program.)

        -------------------CUT-----------------------
        (V6.5) Sentry - DOS/Win/95 Security Program
        Extremely flexible security program allows
        complete customization to fit your needs.
        Protect system, O/S, and/or individual files
        and support up to 100 users with normal and
        "SuperUser" access.  Detailed log files, a
        message system, auditing, expiry dates, and
        non-recoverable deletion help with security
        and system administration.  Network/DESQview
        compatible.
        -------------------CUT-----------------------


        11.5  Date Conversion

        An additional problem with date conversion is that the valid
        date range appears to extend only to 18/01/2038 (the 18th day of
        January, 2038). This is not a serious issue at the moment, as we
        still have over 40 years until that date, however I consider it
        important enough to include in the instructions. I also advise
        system administrators to avoid setting dates higher than this
        limit, as they translate to dates in the past, which will
        cause serious problems.


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
        @echo off
        rem *** Run Sentry.
        c:\sentry\sentry
        rem *** Test to see who logged in.
        rem *** Use the user's login name for the lines below.
        rem *** It must be all caps.
        echo %user% is logging in.
        if "%user%" == "MIKE" goto mike
        if "%user%" == "DANNY" goto dan
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
        Anti-Virus or Norton Anti-Virus, you may find that Sentry will
        show up quite often. The reason for this is that some virus
        scanners record statistics on executable files. When the next
        scan is performed, if the executable files do not match the
        statistics, the scanner panics. This can SOMETIMES be evidence
        of a virus on your system. Sentry modifies itself (in a manner
        very similar to a virus) and so may be picked up on occasion,
        however please be aware that there is no threat from Sentry.

        SENTRY IS NOT A VIRUS!

        Every time you use Sentry, the executable is modified to allow
        for a more secure operating environment. This will cause many
        virus scanner to panic! Do not be alarmed, since this is normal
        operation for Sentry.


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
        execution. Sentry uses this method of deletion on all files,
        regardless of their level of sensitivity.

        This default for this option is on, however it can be turned off
        via the initialization settings.

        This same level of security is found in the external program,
        SDEL. Any files deleted with SDEL cannot be recovered, so take
        care when using it! If you're concerned about who has access to
        SDEL, simply protect it with Sentry, and only the specified
        users will be able to run it.


        11.9  General

        Sentry is written in C++, with most of the code being in regular
        C style. Sentry is compiled with Borland C++ V5.0, and is
        currently over 9000 lines of code. Portability between machines
        is not an issue, since Sentry has been designed and tested on
        standard MS-DOS machines.

        Sentry is verified compatible with Windows 3.x and Windows 95.
        It will work on all processors down to and including 80286's.


        12.0 Potential Threats To Security
        ==================================

        Never underestimate your users. And never be satisfied that your
        system is completely "air-tight". Users are incredibly adept at
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
        NOBODY (not even SuperUsers) can view passwords. (They can never
        be decrypted, remember?) Ultimately, you must be vigilant over
        your system, and try to catch any unusual occurrances as soon as
        possible.

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

        Please be aware that all of these errors cause Sentry to
        lock-up, except where noted. This may be an inconvenience at
        times, but it is done for security reasons (that way an attacker
        can't "induce" an error and get into the system).

        13.1.1  Cannot locate environment.

        This indicates an error with your DOS environment. Make sure
        that you are using the regular environment, or that it is set up
        correctly. This is only a warning, and does not abort execution.


        13.1.2  Environment overflow - not modified.

        There was an error trying to set modify the DOS environment. It
        may occur if you try to run Sentry from within the Sentry DOS
        shell (IE: running Sentry from Windows, then when you're in the
        shell, running it again). If this error occurs, you are
        generally using too many environment variables for the amount of
        space you have allotted. See your DOS manual for ways of
        increasing environment space. This is only a warning, and does
        not abort execution.


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

        This is an error opening one of your system files. If this error
        occurs, make sure that your AUTOEXEC.BAT, CONFIG.SYS and
        MSDOS.SYS (Win 95 users only) files are readable, if they exist.


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
        settings. The easiest way to remedy this is to install Sentry
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

        This error indicates that the registration information was not
        properly entered during registration. Delete the old copy and
        re-install. This error does not occur for Shareware versions.


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

        13.1.23 The Initialization Settings Are Old!

        Somehow, your version of Sentry does not match the version of
        the internal initialization settings. The best way to solve this
        is to export the settings, and re-install the latest version of
        Sentry.


        13.1.24 The Initialization Settings Are New!

        See above.


        13.1.25 Executable Integrity Error!

        This error means that Sentry's executable has been modified by
        an unauthorized source. The most common cause is that your
        system has been infected with a virus. It may also be a sign
        that someone has tampered with your copy of Sentry in an attempt
        to break into your system. To solve the problem, run an
        anti-virus program, and re-install Sentry.


        13.1.26 Error Opening String File!

        This error indicates that the file named "string" (or
        "stringes" for Spanish) is missing or corrupt. Make sure
        the appropriate file is located in the same directory as
        Sentry.exe.


        13.2 Other problems

        Problem: Windows 95 gives CANNOT LOCATE ENVIRONMENT error.

        Some users have reported a problem running Sentry under Windows
        95. The problem is that when Sentry is run, the user gets a
        CANNOT LOCATE ENVIRONMENT error. The cause is that the
        .pif file does not have the appropriate initial environment
        assigned. There is however an easy fix.

        First, open up Explorer, and go into your Sentry directory. Now
        right click on the file called "Sentry.pif" (it may just be
        called "Sentry" but in either case it should have an MS-DOS
        icon). Next select "Properties" and when this comes up click on
        the "Memory" tab. Now just find the "Initial Environment"
        setting (in the "Conventional Memory" box), and change it from
        "Auto" to any value. Even a value as low as 256 works for me,
        but you may have to set it higher depending on your system.


        Problem: High Conventional Memory Usage with Windows.

        When using Sentry with WIndows 95 or Windows 3.x, Sentry may use
        up approximately 160k of conventional memory under certain
        conditions. This memory usage is excessive, and may cause
        problems with other programs. This problem is present in all
        versions of Sentry from V5.2 to V5.6, however should be fixed in
        all versions after V5.6.

        To check for this condition on your system, simply enter a DOS
        box and type the following:

        mem /c/p

        In the listing that is shown, look for an entry called vmm32. If
        the number listed under "Conventional Memory" is over 100k, you
        are probably affected by this problem.

        To fix this problem, simply run Sentry, and go into the
        Super-User menu. From there, select the System Maintenance Menu,
        then the Initialization Settings Menu. Next, go right to the
        bottom and select "Disable CTRL-C." You will probably find that
        the value is set to 1.

        Please read the description of this setting carefully, and
        decide if disabling it is worth the extra memory.

        Please note that even with CTRL-C enabled, a user cannot abort
        out of Sentry when it is running, however they may be able to
        abort out of other programs which you have set up on your
        system.

        Once the change has been made, you must re-start your computer
        to gain the conventional memory back.


        Problem: Sentry is running very slow.

        On some machines it does. It all depends on your processor and
        hard disk speeds. If you want to make it run faster, try using a
        disk caching utility such as Smart Drive. Alternatively, you can
        turn off the "secure deletion" option in the initialization
        settings.


        Problem: I've installed Sentry, but now when I start my computer
        it's prompting me for a login and password.

        Yes, that's what Sentry does. The default login and password are
        both "Sentry" (note the capitalizations). RTFM


        Problem: When I run Sentry, is displays a warning saying I have
        newer/older initialization settings.

        You should probably get the latest version of Sentry (see
        section 11.3 for info on obtaining the latest version). Replace
        all your current files with the files you retrieve. This warning
        may not be a problem in itself, however it is not a good idea to
        use initialization settings from a different version.


        Problem: I get a warning about users being tampered with in the
        log file.

        Someone has been tampering with your users (obviously). They
        thought they could change the SuperUser access on your system,
        but really couldn't. The only side effect of this is that some
        users may appear to have SuperUser access when they don't (and
        vice-versa) when you view them from the SuperUser menu. The
        users' actual access has not changed. To remedy this situation,
        you can get the user to enter another password (this can easily
        be done by expiring their current password). As soon as the new
        password is entered, the problem will disappear.


        Problem: I can't log in at all.

        Are you a user on the system? Are your initialization settings
        set up correctly? Have you run the install program?


        Problem: I can't log in as a SuperUser.

        Did you give yourself SuperUser access? Are you remembering to
        hold down CTRL when you hit enter?


        Problem: My account information is corrupt or deleted.

        Pray you kept a backup somewhere. At the very least, you should
        have the install program sent with Sentry. In that case,
        re-install, and log in as Sentry. Since Sentry is initially a
        SuperUser, you can re-create your users (don't forget to delete
        the Sentry user when you are finished!).


        Problem: I can't create a c:\Sentry directory on my drive.

        If you are using MS-DOS's UNDELETE program, it may create a
        directory called "Sentry" off of your root directory. This
        directory is hidden, and can only be seen with the "dir /a"
        command. (This only occurs if you are using the "delete sentry"
        mode). Possible fixes are to stop using "delete sentry" mode, or
        to create your Sentry directory as something else (eg:
        c:\Sentry2, c:\Secur\Sentry, etc etc).


        14.0 Standard Disclaimer
        ========================

        As usual, I accept no responsibility for any loss, damage or
        inconvenience that may be caused either directly or indirectly
        by any material in this package.

        Inexperienced users should take care with this program, as you
        may lock yourself out of your computer, or worse!

        If you feel you want to use it, but don't feel completely
        confident, leave a "back door" for you to use. (IE: don't
        implement all of the security measures listed in "Securing Your
        Computer"), so that if you DO get locked out, you can still get
        in using the back door. Once you are satisfied that all is well,
        lock up the back door too.

        Additionally, I would like to make it clear that Sentry is in no
        way connected to Nortel, BNR or Northern Telecom. All of
        Sentry's development has been completed on my own personal time,
        using my own personal resources.

        Please read the document "LICENSE.TXT" included with this
        software for the entire licensing agreement.


        15.0 Contact Information
        ========================

        I would greatly appreciate any comments you might have about
        this program (either positive or negative). If you encounter any
        problems, or have a suggestion for making Sentry better, please
        let me know, and I'll try to put it in a future release. I look
        forward to hearing from you.

        You can contact me via e-mail at info@cipherlogic.on.ca and I
        will reply as quickly as I can. If you do not have internet
        access, you can contact me via surface mail at:

        Cipher Logic Canada Inc.
        PO Box 412
        Munster, ON
        K0A 3P0
        Canada


        16.0 About the Author
        =====================

        Mike Bobbitt is currently a Security Developer for Nortel in
        Ottawa, Ontario Canada. He is a graduate of Acadia University,
        with a bachelor's degree in Computer Science, Specializing in
        Software. Mike has spent a significant portion of his personal
        and professional time researching computer security
        technologies.

        His primary interests have always been in the area of computer
        security, which in part prompted him to create Sentry.



        17.0 Credits
        ============

        My thanks go out to these people:

        Everyone who uses Sentry for making it popular world wide.

        Everyone who has registered Sentry for their support.

        Mark Saarinen for the UNIX crypt() implementation.

        Richard Brittain for use of his DOS environment variable code.

        Everyone who has taken the time to comment and help make Sentry
        a better package, including:

        Dexter J. Caldwell for suggestions on various options, including
        the "template" methodology for protected files.

        L.D. Best for suggestions, comments and bug reports, as well as
        detailed explanations of test situations. L.D. has provided
        many good ideas and useful comments with respect to Sentry, and
        has assisted greatly in "fine tuning" many features such as file
        protection.

        Bret Jacobsen for finding some serious errors in the first
        release, as well as continually making suggestions for
        improvement. Bret has given invaluable assistance in the
        development of Sentry.

        Juan A. de Uriarte jr for the translation to Spanish.


        ...And my wife for listening to me talk incessantly about it.
