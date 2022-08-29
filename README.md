# Mavs Arboretum

## Table of Contents
- Mavs Arboretum in C++
  * [About the Project](#about-the-project)
  * [Compile Instructions](#compile-instructions)
  * [Saving And Opening Stores](#saving-and-opening-stores)
  * [Project Demo Video](#project-demo-video)
  * [SCRUM Spreadsheet](#scrum-spreadsheet)
  * [Known Issues](#known-issues)
  * [Project UML Class Diagram](#project-uml-class-diagram)

## About the Project
This C++17 project offers a friendly user interface for a hypothetical gardening store (using the C++ gtkmm library). Making use of a [Makefile](https://www.gnu.org/software/make/manual/make.html) makes it easy to compile and run the program. The store's structure is based on a number of classes that work together through object-oriented programming. [UML class diagrams](https://github.com/RobertCarrUTA/Mavs-Arboretum-Store/blob/main/UML-Class-Diagram-Requirements.png) guided the design of the program.

## Compile Instructions
The following compile instructions are for Ubuntu. In addition, we assume you have all the required files and are entering them in the directory containing those files.
* compile: Using the terminal, navigate to the directory where these files are located, and then enter "make" to compile the program.
* run: Using the directory where "make" was run, enter "./manga"
* clean: Enter "make clean" to delete the executable file and all its object files

## Saving And Opening Stores


***Saving a store:***


Make sure the **.manga** file extension is added when saving a store.
* An example would be MyStore.manga


***Opening a store:***


To open a previously saved store ([I have provided one here](https://github.com/RobertCarrUTA/Mavs-Arboretum-Store/blob/main/saved-stores/Store1.manga)), select open store from the toolbar and choose the saved store file.

## Project Demo Video
[Click here to see the project demo](https://www.youtube.com/watch?v=xdmtEtFTomY).

## SCRUM Spreadsheet
The 6 week SCRUM spreadsheet for the project can be found by [clicking here](https://github.com/RobertCarrUTA/Mavs-Arboretum-Store/blob/main/documents/Scrum_MANGA.ods). Using a Linux operating system is recommended for viewing the spreadsheet.

# Known Issues
* Hitting the cancel button when creating a new store will cause the program to crash. The program will not crash if you hit X on the window or press ESC. Fixing this is on my to-do list.
* The program crashes if a user clicks the X on the Add New Order window when the customer list is empty. A new order will be created for a customer if the customer list is not empty and the user clicks the X on the window. In contrast, pressing the Cancel button does not cause it to crash, pressing ESC does cause it to crash. Fixing this is on my to-do list.

## Project UML Class Diagram
This project was designed and implemented using the UML class diagram shown below.
![alt text](https://github.com/RobertCarrUTA/Mavs-Arboretum-Store/blob/main/documents/UML-Class-Diagram-Requirements.png)
