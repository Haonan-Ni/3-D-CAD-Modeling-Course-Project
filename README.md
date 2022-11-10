# 3-D-CAD-Modeling-Course-Project
## Project Introduction
This project is to realize the five basic Euler operations based on the half-edge data structure according to the requirement of the final course project of 3D CAD modeling delivered by Prof. Gao. 

## Review of Half-edge Data Structure
The half-edge data structure, improved from the wing-edge by Mantyla long time ago, has now become the main stream data structure for representing the topological relations in 3-D modeling for its high efficiency in edge data structuring and practical application.
The core concept of the half-edge data structure is that a physical edge is represented as two edges, and each edge is only related to a face (hence its name). In essence, the half-edge contains only half the information of a physical edge. A simplified half-edge data structure is presented as:

![a8a0b8cf6b127758e7a70d5a1280ba4](https://user-images.githubusercontent.com/86988075/200841191-65efc5b0-6690-4df2-a99d-093bf9e82320.jpg)

Half edges, edges and vertices consists the core of this entire data structure. The following map represents the hierarchy of half-edge data structure:

![462301aa778a4fdc437ec56b671d065](https://user-images.githubusercontent.com/86988075/200841216-05ace4ec-1a49-4b3f-be1d-33672696a67a.jpg)  

## Review of Euler Operations
The concept of Euler operation was put forward by B.G. Baumgart in 1972 to provide an effective and correct method for establishing complex boundary data structures of three-dimensional objects (to ensure validity and universality). It is based on the Euler formula:

![86adc1ac4d40b16bb213bbf7541073f](https://user-images.githubusercontent.com/86988075/200841267-17df2aed-495d-4f6e-8feb-e6d2ea12ee3e.jpg)

It is this theoretical basis that provides a set of universal and complete topology operations of B-rep and supports the validity for 3-D modeling.
The mechanism of five basic Euler operators mentioned beforehand are listed in the table below:

![3846657659f0930109338ade190619e](https://user-images.githubusercontent.com/86988075/200841307-c71e5f8f-2828-439f-b856-c1e796ae5642.jpg)

·mvsf (v, f ): To generate a face containing a vertex and form a new solid.
·mev (v1, v2, e): To generate a new vertex v2, connect the point to the existing vertex v1, and construct a new edge.
·mef (v1, v2, f1, f2, e): To connect two vertices v1 and v2 on face f1 to create a new edge e and a new face f2.
·kemr (e): To delete edge e to generate a new inner ring on one of its adjacent faces.
·mekr (v1, v2, e): To connect vertices v1 and v2 to generate a new edge e, and delete an inner ring on the face of v1 and v2.
·kfmrh (f1, f2): To delete face f2 in contact with face f1, generate an inner ring on face f1, and form a through-hole on the solid.
## Program Structure
The project is developed on programming tool Visual Studio 2022. In the project, the head file “Half_Edge_DS.h” contains the complete definition and coding of half-edge data structure. The source file “Euler_operators.cpp” includes the five basic Euler operators “mvfs”, “mev”, “mef”, “kemr”, “kfmrh”, and the additional “sweep”, together with a data store function that saves all vertices, loops, and faces created by each Euler operation step into a .brp file for later display in MeshFramework. Because OpenGL is not employed for graphical display, all environment should be able to run the program with ease. The source file “main.cpp” is where the interface are generated and all actual Euler operations happen. The beginning instruction describes the five separate sections that make up the whole “main” source file originally. By default, section 1, 2, 3 creates three individual quadrilaterals in 2-D x-z plane, which means 4 vertices in each section. Section 4 integrates the “sweep” function to extrude in the third dimension to create 3-D solid based on the planar quadrilateral and the “kfmrh” function to make ring holes if there are inner rings (instruction displayed at the beginning of the program as well).

![b5f708836fbe18ad8549bcde6db6f4d](https://user-images.githubusercontent.com/86988075/200841357-491c9dfa-0df7-4d5d-b57e-6694a3142635.jpg)

## User Manual
The program provides three options for users to interact. If you input “d”, the program will tell you the number of the current vertex and the values of default inputs, and you will follow the default demonstration that shows the structure of the program and see each steps till the end.

![a81a34dfcac45ebeec779e29b98a697](https://user-images.githubusercontent.com/86988075/200847514-cb05e980-5934-4c8d-80ac-52ef49a9faed.jpg)

For convenience, an option of when you input ‘s’ to skip all the default steps are also considered in the program.

![360a1a98970d659318725b870ee530f](https://user-images.githubusercontent.com/86988075/200841450-aedc7766-38ab-4207-8be2-d26f0addfd8c.jpg)

Customization is also available in the program. Input “c” in the interface, the program tells you the vertex you are currently creating and the correct input format.

![8046f900f0edd54dd8172a5fd359eff](https://user-images.githubusercontent.com/86988075/200847597-b113ef9f-dda6-4992-8ece-f61e995dd6d3.jpg)

However, if you input the wrong format, the program warns you of format error and terminates.

![c9ba452d44cf42387c36dfa105e329a](https://user-images.githubusercontent.com/86988075/200847660-f371cc0d-9aac-4021-b1c2-a2c09596b92f.png)

MeshFramework is quite simple and easy to use. Just open the software and use “open” command in the “file” categories to open the newly generated “B-rep_Result.brp” file in the CADproject\CAD folder. The following pictures shows the solid model created by default and custom vertices inputs in MeshFramework:

![38fb91e1a4003bfd45df1a05ee87281](https://user-images.githubusercontent.com/86988075/200841625-9549e03d-3f4c-45c3-ae03-36480e6a8038.jpg)

![fc82bd6fd059b30230490f41113f7d2](https://user-images.githubusercontent.com/86988075/200848219-b77dc280-2798-4da7-9e58-a4034506e627.jpg)

![a8d14b88438bb0d1dae9d1921376f52](https://user-images.githubusercontent.com/86988075/200841652-bd1d972f-fd93-4b99-92f2-eb52f2fd78c2.jpg)

MeshFramework also allows you to switch from solid paint to wire paint or vertex point, as shown below:

![d1e77a29cabbc0c1fae7ac3c6519ba6](https://user-images.githubusercontent.com/86988075/200848241-3d9e15bb-2807-4952-8536-6d0dff58b155.jpg)

You are also allowed to change the default topological structure of the program to reshape different solids or make more holes in the “main” source file if not satisfied with simple hexahedron. But be advised that this behavior is highly dangerous as you might create incorrect topological structures that MeshFramework cannot load. So far, this program does not support for generating multiple solids.

![4495c8d28d3c8d9ec89455593e7670e](https://user-images.githubusercontent.com/86988075/200847942-267a55b0-16bc-4864-9ad0-c4f080775896.jpg)

## Reference
1. Prof. Gao. Lecture notes (2022), 3-D CAD Modeling. Zhejiang University.
2. Mäntylä M. An introduction to solid modeling[M]. Computer Science Press, Inc., 1987.
3. Shah J J, Mäntylä M. Parametric and feature-based CAD/CAM: concepts, techniques, and applications[M]. John Wiley & Sons, 1995.
4. 唐荣锡, 汪嘉业, 彭群生. 计算机图形学教程[J]. 北京: 科学出版杜, 1990: 20-75.
