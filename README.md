## Pactus (historical)

A simple keylogger for Windows.

**Historical/educational archive only.** This is a translation and archival description of a personal project I wrote in 2004. The original program is a local keylogger intended to capture other people's input without their consent. I no longer endorse or recommend creating or using such software — doing so is unethical and may be illegal in many jurisdictions. This repository (if created) should be used only for historical study or secure, consented research in controlled environments.

### Summary

Pactus is a small, local Windows keylogger I developed in 2004. It was designed to record keyboard input to a local file (`C:\WINDOWS\go_l.daf`) and was distributed/installed manually on target machines.

### Background / Motivation

My goal at the time was to spy on my classmates’ MSN conversations and capture their MSN passwords in the school's lab.

Antivirus software did not detect it and neither did the firewall, since it didn't need the Internet to run. We organized weekly sessions to collect the `go_l.daf` files from the lab machines over the local network during computer classes.

This project was meant to be just a module or part of a much larger one where we would spy on everyone and, jokingly at the time, "dominate the whole world."

Although today these motivations are clearly unethical, I have a lot of affection for this project because with it I had to learn a lot of things:

- [C programming](https://en.wikipedia.org/wiki/C,_The_Complete_Reference)
- [Win32 programming](https://winprog.org/tutorial/), including DLLs
- how to read [dense documentation about Windows internals](https://learn.microsoft.com/en-us/windows/win32/winmsg/hooks)
- and how to ask questions in English on [IRC](https://winprog.org/).

### How it worked

Installation was manual. The user was instructed to copy `pactus_run.exe` and `pactus_dll.dll` to `C:\Windows\` or some other "hidden" directory.

When executed, it added itself to the registry for autostart under the super-secret name `WSAConst`. It also hid itself from the Windows process list.

It created the file `C:\WINDOWS\go_l.daf` where everything the user typed was saved — the user was also advised never to associate the `.daf` extension with Notepad, to avoid being "discovered".

Internally, `pactus_run.exe` called a routine in `pactus_dll.dll` that started the keylogger by registering a global hook in Windows that monitored keyboard events `WM_CHAR` and `WM_KEYUP`.

It also logged the current window name to give context about what the user was doing.

### How to use it

Don't.

**Disclaimer:** This document is for historical/educational reference only. Do not use or redistribute software for intrusive or non-consensual surveillance.
