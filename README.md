# Mechanical Cherry MX blue keyboard emulator for Mac OS X

`keyclacker` is a daemon that plays sounds of mechanical keyboard when you
press keys on your Mac keyboard. For those occasions when you cannot bring your
mechanical friend with you.

See [this tweet](https://twitter.com/TheRealSpajus/status/888009860788473856)
for a demo video.

Code is forked from and based on this keylogger:
[caseyscarborough/keylogger](https://github.com/caseyscarborough/keylogger)

All key logging functionality was removed, your keystrokes are not being
recorded.

## Usage

Start by cloning the repository and running the proper make commands, shown
below. By default, the application installs to `/usr/local/bin/keyclacker`,
which can easily be changed in the
[`Makefile`](https://github.com/spajus/keyclacker/blob/master/Makefile).
`make install` requires root access.

```bash
$ git clone https://github.com/spajus/keyclacker && cd keyclacker
$ make && sudo make install
```

```bash
$ sudo keyclacker
```

If you'd like the application to run on startup, run the `startup` make target:

```bash
$ sudo make startup
```

## Uninstallation

You can completely remove the application from your system (including the startup daemon) by running the following command (logs will not be deleted):

```bash
$ sudo make uninstall
```

### Optional Parameters

You can pass the volume value for the program (default volume is 1, which is
pretty quiet)

```bash
# Clear the logfile.
$ keylogger clear
Logfile cleared.

# Specify a logfile location.
$ keylogger ~/logfile.txt
Logging to: /Users/Casey/logfile.txt
```

## Contributing

Feel free to fork the project and submit a pull request with your changes!
