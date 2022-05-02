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

## Code Style

The coding style for Mesopotamic is laid out [here](CodingStyle.md). However these are only particularly strict when working on external parts, like the user readable include headers

## Main Header

If you are producing a module that has a main header, look at solomon.h for an example, then there are certain rules that have to be followed as well. All functions must have a java docs style commenting 

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
SolomonWindow solomon_window_create(int x, int y, int w, int h, char* title);
```

At the top of the main header, you should have introduction to the module. That is the name of the module, description, license, copyright, authors. This is then wrapped in ***'s Once again look at solomon.h for an example.

### Header Guards 

Header guards are delimited with double underscores, and it goes `__projectname_EXTERNAL_HEADER__` for example, lets look at Solomon once again 

```c
#ifndef __SOLOMON_EXTERNAL_HEADER_H__
#define __SOLOMON_EXTERNAL_HEADER_H__ (1)
```

## Meso Prefix

The only projects that should specifically have a "meso" prefix to their module name are those that go in the helper functions. Why do we do this? because the helper functions don't obviously belong to a specific project. 

If you're using something like Clay or Ziggurat, then they are such a huge part of the control flow that users should know where they come form. Also more significant projects should try to have a creative name attached to them. Where as helper functions just need to be straight to the point.  