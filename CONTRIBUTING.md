***Getting started contributing***

1. First, make sure you have WSL installed (along with g++). This step is not necessary if you are on Linux.
2. Ensure you have git installed. In most cases, it will come with WSL or Linux.
3. Install CMake (on WSL if using windows). This is essential because CMake will be the tool we use to build our project. It might help to install the CMake extension in VSCode.
4. Clone the repository. 
5. This project will be using a library called SFML for graphics. You will need to have this installed (along with dependencies) in order to be able to build the project on your computer. Info on installing SFML can be found at https://www.sfml-dev.org/tutorials/2.6/start-linux.php, and info on installing its dependencies can be found at https://www.sfml-dev.org/tutorials/2.6/start-cmake.php, in the section titled "Requirements"
6. Please name the directory you build the project in "build". This is necessary to ensure that git ignores these files, since we don't want this diectory to become a part of the repository. 

   *More information to be added later*

commands to build/run project:
	1) cmake --build build
	2) ./build/enm_learning_aid
