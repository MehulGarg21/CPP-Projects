**Objectives**
This lab is an exercise on inheritance and virtual functions, which are powerful code reuse mechanisms of C++. More specifically, you will enhance a program that implements a database of shapes that stores, manipulates, and “draws” new shapes that did not exist when the program was written.

**Problem Statement**
You are provided with a framework that implements a database of shapes, in the form of an object file. Without changing the code of this framework (you really cannot since you do not have the source), you will add new functionality simply by adding three new classes (Circle, Triangle and Rectangle). The framework provides the “higher-level” decision making of the program, and you add new features by creating new classes that the framework calls when appropriate, via virtual functions. This is a powerful form of code re-use; the framework is making use of objects that did not exist when it was written.
