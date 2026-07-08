<h1 align="center">PomodoroTimer</h1>
<p align="center">A simple configurable pomodoro timer application</p>

## Getting started
The application does not have any external dependencies. To build it, first clone the repository
with the next command:

```
  git clone https://github.com/IkerGalardi/PomodoroTimer.git
```

Build the application with the next command:

```
  make
```

By default the timer starts in resting mode, and has 25 minutes for work and 5 minutes for rest. If
that configuration does not suit you, change the configuration (defines starting with `CONFIG_`) 
to suit your needs.

## Usage

The application is really simple. When opening the application, a window will start the countdown as
configured at compile time. That's it!

## Roadmap
The application is now in a preliminary state. Even though right now it suits my basic needs, the
next are some planned features I wan't to add in order to consider the application in version 1.0.0:

- [X] Progress bar and state text
- [X] Sounds when changing states
- [X] Background white noise
- [X] Add a way to pause and restart the timer
- [ ] A way to configure it graphically
- [X] Proper support for MacOS (icon, persistence)
- [ ] Proper support for Linux (icon, persistence)

The next are the supported (and planned) platforms:
- [X] MacOS (ARM64)
- [ ] Linux (ARM64)
- [ ] Linux (x86)

The windows platform support is not planned, as I dont have any windows machine laying around in
order to properly support and test the application, although PR related to the platform are
welcomed.

## Contributing

If you want to add any feature or fix any bug simply fork the repository and create a pull request
with the desired feature or fix. I just want a simple pomodoro application, so if you have an
advanced feature need, fork the repo and go your own path :)
