### Hightale Repo

Currently we are using [Godot 3.2.2](https://godotengine.org/download/windows)  
[alt if link oudated](https://downloads.tuxfamily.org/godotengine/3.2.2/)  
  
GDNative code is contained in the scr folder.  
Inorder to build it run the following command in VS Native Tools Command Prompt.  
```
scons platform=<platform>
```

It will build to project/win64.  
To change output folder for the build, go in the SConstruct file in the main folder.  
Then change 'win64/' to something new in the following line  
```
env['target_path'] += 'win64/'
```

### Getting Started

Make sure you have python installed and set to path.  
Also have scons installed, some version of VS Native Tools CMD and Godot.  
Make sure to add a copy of godot-cpp and godot-cpp/godot-headers in your main folder.  
You may need to get a version from someone else rather than git.  

Additional help for running godot native can be found [on the godot wiki](https://docs.godotengine.org/en/stable/tutorials/plugins/gdnative/gdnative-cpp-example.html), [the godot-cpp readme](https://github.com/godotengine/godot-cpp) or from this [youtube tutorial](https://youtu.be/XPcSfXsoArQ?t=196).  

### Writing GDNative

When you make a class you have to register it in NativeLib.cpp in the godot_nativescript_init method. otherwise it will not show up.  
Add a line inside that method that looks like this ->
```
godot::register_class<Controls>();
```
Instead of controlls you will put your class name.  
You must also register class fields and methods so they show up in the inspector.  
Evey class created must have a void \_register_methods()  
This is where you register methods, properties and signals to be seen in godot.  
This allows these methods to been seen within the godot editor. Sort of like serialization in unity.  
Primarily we will use this method ->  
```
register_property(ClassName, PropertyType)("PropertyName", &ClassName::PropertyName, DefaultDisplayValue);
```
Make sure the the default display value matches the default value in the actual code.  
More info [here](https://youtu.be/XPcSfXsoArQ?t=630).
  
For every class you will have to set up a Godot Nativescript in the editor.
Usually all you have to do is type in the name.
More info is [here](https://youtu.be/XPcSfXsoArQ?t=844).
