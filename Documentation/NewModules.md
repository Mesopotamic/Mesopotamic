# Adding a New Module

So you want to add a new module to Mesopotamic! That's fantastic! Let's go over the conventions for getting started. If you can make your project name a clever pun relating to ancient Mesopotamia that would be great! But it's also fine if you choose not to! i.e. How do I make a pun about xml?? 

## Folder Structure

Each project has to follow the same rules for the folder layout 

* CMakeList.txt in the root directory of the repo
* All .c files are contained in the Source directory
* The EXTERNAL headers are placed in the Include directory
* Must contain a README.md in the root directory
* All other markdown files go in Documentation directory
* Documentation Images go inside the Documentation/Images directory 

## Main Header

If you are producing a module that has a main header, look at Solomon.h for an example, then there are certain rules that have to be followed as well. All functions must have a java docs style commenting 

```c
/**
 * @brief Allocates a Solomon window, on the heap and then hands the basic details over to the internal handle
 * @param x X position of the top left corner of the window (-1 lets the OS decide)
 * @param y Y position of the top left corner of the window (-1 lets the OS decide)
 * @param w Width of the window in pixels
 * @param h Height of the window in pixels
 * @param title The heading given to the window title
 * @returns Opaque handle to the pointer containing the window data
 */
SolomonWindow SolomonWindowCreate(int x, int y, int w, int h, char* title);
```

At the top of the main header, you should have introduction to the module. That is the name of the module, description, license, copyright, authors. This is then wrapped in ***'s Once again look at Solomon.h for an example.

### Header Guards 

Header guards are delimited with double underscores, and it goes `__projectname_EXTERNAL_HEADER__` for example, lets look at Solomon once again 

```c
#ifndef __SOLOMON_EXTERNAL_HEADER_H__
#define __SOLOMON_EXTERNAL_HEADER_H__ (1)
```

## Function & Enum Names

So how do we name functions? We start with the name of the project, if it's an Enum we then add an Enum after the project name. 

After that functions are then named with the scope getting more specific, so for example for creating a Solomon Window we go: Solomon -> Window -> Create

```c
// Great!
SolomonWindowCreate();

// Nope
SolomonCreateWindow();

// Nope
CreateSolomonWindow();
```

 