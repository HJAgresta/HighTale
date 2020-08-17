### Hightale Repo

Currently we are using [Godot 3.2.2](https://godotengine.org/download/windows)  
[alt if link oudated](https://downloads.tuxfamily.org/godotengine/3.2.2/)  
  
GDNative code is contained in the scr folder.  
Inorder to build it run the following command in VS Native Tools Command Prompt.  
```
scons platform=<platform>
```

It will build to project/win64.  
To change output folder for the build set in in the SConstruct file in the main folder.  
Change 'win64/' to something new in the following line  
```
env['target_path'] += 'win64/'
```

### Getting Started

Make sure you have python installed and set to path.  
Also have scons installed, some version of VS Native Tools CMD and Godot.  
Make sure to add a copy of godot-cpp and godot-cpp/godot-headers in your base folder.  
You may need to get a version from someone else rather than git.  

Additional help for running godot native can be found [on the godot wiki](https://docs.godotengine.org/en/stable/tutorials/plugins/gdnative/gdnative-cpp-example.html), [the godot-cpp readme](https://github.com/godotengine/godot-cpp) or from this [youtube tutorial](https://www.youtube.com/watch?v=XPcSfXsoArQ).  
