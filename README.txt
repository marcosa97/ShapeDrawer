ECS175 PROJECT 2:
Name: Marcos Alcantar
Student ID: 913133174
email: mualcantar@ucdavis.edu

|***************|
| INSTRUCTIONS: |
|***************|

1) Once the file is unzipped, navigate to the directory containing all the project files "p2" and
   type in the command "make" to compile the program.

2) Run the executable file using the command "./p2.out"

3) The following Menu will be displayed in the terminal, along with a window with 4 empty subwindows:

		Please enter the number for which operation you wish to perform:
            1) Read in 3D polyhedra objects from a .txt file.
            2) Perform a 3D translation on an object.
            3) Perform a 3D rotation about a specified axis on an object.
            4) Perform a 3D scaling on an object.
            5) Remove an object from the scene.
            6) Remove all objects (clear screen).
            7) Print out polyhedra vertex coordinates.
            8) Exit Program (and write current objects to file 'output.txt').

    Type the number for the operation you want to perform and press ENTER.

4) Once you have read in objects, they will be drawn in 4 different projections: 
       a) Top left box = XY plane
       b) Top right box = XZ plane
       c) Bottom left = YZ plane
       d) Bottom right = Cabinet projection with a 45 degree view in the XY plane.
          NOTE: In this view, some objects will get clipped or not displayed.

   The green lines in the XY, XZ, and YZ windows are the coordinate axes.
   The bottom right subwindow doesn't have the axes drawn.

|************************|
| INFO ABOUT OPERATIONS: |
|************************| 

  * OPERATION 1) To read in objects from a file, you will need to have the text file in the same directory
    as all of the program files. When you choose this option, you will be prompted to enter the 
    file's name. 
    	
    	***A sample file, called test2.txt, has been provided, with 3 objects.***

        INPUT FILE FORMAT: Same as the one provided in the homework sheet. Coordinates are in World Coordinates:

        2              ->number of objects

		4              ->Object 1: number of vertices
		0.0 0.0 0.0    ->vertices
		1.0 0.0 0.0    
		0.0 1.0 0.0    
		0.0 0.0 1.0    
		6              ->number of edges
		1 2            ->edges
		1 3
		1 4
		2 3
		2 4
		3 4
                       ->Objects separated by a blank line
		4              ->Object 2
		1.8 1.5 0.5
		2.0 3.0 0.0
		0.5 2.0 2.0
		1.5 2.0 3.0
		6
		1 2
		1 3
		1 4
		2 3
		2 4
		3 4

  * OPERATIONs 2-4) For these operations, the vertices and edges info for each object will be printed in the terminal.
    Type in the ID number for the object you want to transform, and then enter the information that is asked for. If
    asked to input coordinate points, enter World Coordinates. 

        ***After rotating an object, a red line representing the points chosen for axis of rotation will be drawn.
           It will not be shown if it's outside of the bounding box.

  * OPERATION 5) Enter the ID number for the polygon you want to remove from the scene and press ENTER. 

  * OPERATION 6) Removes all objects from the scene.

  * OPERATION 7) Prints vertex coordinates for an object. Enter 0 if you want to print vertices for all objects.

  * OPERATION 8) Ouput file will be written to a new output file called "output.txt". 


|*************************|
| ALGORITHMS IMPLEMENTED: |
|*************************|

    NDC System conversions in polygon.cpp, lines 8-41,                         (convertWCtoPC function)
    Dynamic Bounding Box in boundingBox.cpp, lines 7-52                        (updateBoundingBox function)
	3D Object Translation in transformations3D.cpp, lines 127-181              (handleTranslate function)
	3D Object Scaling in transformations3D.cpp, lines 389-430                  (handleScale function)

	* FROM TEXTBOOK:
          3D Object Rotation in transformations3D.cpp, lines 340-359.          (handleRotate function)
                                                                               (rotation matrix created in rotate3D function)
	      DDA Line Drawing implemented in lineAlgorithms.cpp, lines 28-54      (lineDDA function)     