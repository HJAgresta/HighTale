### Hightale Repo

Currently we are using Godot 3.2.2

GDNative code is contained in the scr folder.
Inorder to build it run the command in VS Native Tools Command Prompt.
```
scons platform=<platform>
```

It will build to project/win64.
To change output folder for the build set in in the SConstruct file in the main folder.
Change 'win64/' to something new in the following line
```
env['target_path'] += 'win64/'
```
