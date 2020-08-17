### Hightale Repo

Currently we are using Godot 3.2.2

GDNative code is contained in the scr folder.
Inorder to build it run the command in VS Native Tools Command Prompt.
It will build to project/win64, inorder to change this edit the SConstruct file in the base folder.
```
scons platform=<platform>
```