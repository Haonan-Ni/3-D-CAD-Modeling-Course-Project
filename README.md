# 3-D-CAD-Modeling-Course-Project
#Project Introduction
      This project is to realize the five basic Euler operations based on the half-edge data structure according to the requirement of the final course project of 3D CAD modeling delivered by Prof. Gao. In the project, the Euler operations, along with the extra “Sweep (Extrusion)” operation based on the half-edge data structure have been defined and programmed in C++ to represent the topological relations of vertex, edge, and faces. In addition, the sweeping function allows for multiple inner rings on 2D sketch. However, because I was unfamiliar with OpenGL and couldn’t get it to work properly anyhow, too much time was wasted previously in vain and I finally decided to use a public open software MeshFramework for model viewing after topological generation (possibly minus points for lack of programming work).
      
#Review of Half-edge Data Structure
      The half-edge data structure, improved from the wing-edge by Mantyla long time ago, has now become the main stream data structure for representing the topological relations in 3-D modeling for its high efficiency in edge data structuring and practical application.
      The core concept of the half-edge data structure is that a physical edge is represented as two edges, and each edge is only related to a face (hence its name). In essence, the half-edge contains only half the information of a physical edge. A simplified half-edge data structure is presented as:
      
      ![a8a0b8cf6b127758e7a70d5a1280ba4](https://user-images.githubusercontent.com/86988075/200838125-adf81d18-11e7-4f59-ada2-1ce7f2886722.jpg)
      
      Half edges, edges and vertices consists the core of this entire data structure. The following map represents the hierarchy of half-edge data structure:
      
      ![462301aa778a4fdc437ec56b671d065](https://user-images.githubusercontent.com/86988075/200838242-afec8345-60c0-4d1b-b953-4033d1a51a65.jpg)
      
#Review of Euler Operations
      The concept of Euler operation was put forward by B.G. Baumgart in 1972 to provide an effective and correct method for establishing complex boundary data structures of three-dimensional objects (to ensure validity and universality). It is based on the Euler formula:
      
      ![86adc1ac4d40b16bb213bbf7541073f](https://user-images.githubusercontent.com/86988075/200838386-147ba991-af7d-4df1-b223-ce9ce7607c4a.jpg)
      
      It is this theoretical basis that provides a set of universal and complete topology operations of B-rep and supports the validity for 3-D modeling.
      The mechanism of five basic Euler operators mentioned beforehand are listed in the table below:
      
      ![3846657659f0930109338ade190619e](https://user-images.githubusercontent.com/86988075/200838465-4faa43b6-a1df-4cf1-b21b-7d42315ad172.jpg)
      
      ·mvsf (v, f ): To generate a face containing a vertex and form a new solid.
      ·mev (v1, v2, e): To generate a new vertex v2, connect the point to the existing vertex v1, and construct a new edge.
      ·mef (v1, v2, f1, f2, e): To connect two vertices v1 and v2 on face f1 to create a new edge e and a new face f2.
      ·kemr (e): To delete edge e to generate a new inner ring on one of its adjacent faces.
      ·mekr (v1, v2, e): To connect vertices v1 and v2 to generate a new edge e, and delete an inner ring on the face of v1 and v2.
      ·kfmrh (f1, f2): To delete face f2 in contact with face f1, generate an inner ring on face f1, and form a through-hole on the solid.

#Program Structure
      The project is developed on programming tool Visual Studio 2022. In the project, the head file “Half_Edge_DS.h” contains the complete definition and coding of half-edge data structure. The source file “Euler_operators.cpp” includes the five basic Euler operators “mvfs”, “mev”, “mef”, “kemr”, “kfmrh”, and the additional “sweep”, together with a data store function that saves all vertices, loops, and faces created by each Euler operation step into a .brp file for later display in MeshFramework. Because OpenGL is not employed for graphical display, all environment should be able to run the program with ease. The source file “main.cpp” is where the interface are generated and all actual Euler operations happen. The beginning instruction describes the five separate sections that make up the whole “main” source file originally. By default, section 1, 2, 3 creates three individual quadrilaterals in 2-D x-z plane, which means 4 vertices in each section. Section 4 uses the “sweep” function to extrude in the third dimension to create 3-D solid based on the planar quadrilateral. Section 5 employs the “kfmrh” function to make ring holes on the 3-D solid model (instruction displayed at the beginning of the program as well).
      
      ![b5f708836fbe18ad8549bcde6db6f4d](https://user-images.githubusercontent.com/86988075/200838711-028103c9-d64f-4428-96da-b9ffbfa6a88b.jpg)
      

#User Manual
      The program provides three options for users to interact. If you input “d”, the program will tell you the number of the current vertex and the values of default inputs, and you will follow the default demonstration that shows the structure of the program and see each steps till the end.
      
      ![c574f63538ab4016a93506f313d9fa4](https://user-images.githubusercontent.com/86988075/200838889-dc112b00-35ea-43d0-ae73-9545ca0d0958.jpg)
      
      For convenience, an option of when you input ‘s’ to skip all the default steps are also considered in the program.
      
      ![360a1a98970d659318725b870ee530f](https://user-images.githubusercontent.com/86988075/200839088-347275f6-1e45-4459-87d2-1b9ba0bae94b.jpg)
      
      Customization is also available in the program. Input “c” in the interface, the program tells you the vertex you are currently creating and the correct input format.
      
      ![23190e1703f7bc6277b1ef5eaa0c4f3](https://user-images.githubusercontent.com/86988075/200839225-3dd43d6a-e7b9-4636-a5e9-84b2f65650a8.jpg)
      
      However, if you input the wrong format, the program warns you of format error and terminates.
      
      ![fbbfa200af9b1e473c2735076c211d8](https://user-images.githubusercontent.com/86988075/200839301-29e0bc0a-1455-4df4-aa1d-22f5430c6260.jpg)
      
      MeshFramework is quite simple and easy to use. Just open the software and use “open” command in the “file” categories to open the newly generated “B-rep_Result.brp” file in the CADproject\CAD folder. The following pictures shows the solid model created by default and custom vertices inputs in MeshFramework:
      
      ![38fb91e1a4003bfd45df1a05ee87281](https://user-images.githubusercontent.com/86988075/200839398-a5f931e3-0f74-465d-9942-c3d24989ad8c.jpg)
      
      ![e73b889e6db5926e851ff5be59b171b](https://user-images.githubusercontent.com/86988075/200839439-307a4c1c-ef8e-4ab7-a8fa-6f5791ac4141.jpg)
      
      ![a8d14b88438bb0d1dae9d1921376f52](https://user-images.githubusercontent.com/86988075/200839492-7b62c44e-7591-4567-b7b6-cc6a4e432261.jpg)
      
      MeshFramework also allows you to switch from solid paint to wire paint or vertex point, as shown below:
      
      ![d1e77a29cabbc0c1fae7ac3c6519ba6](https://user-images.githubusercontent.com/86988075/200839625-a941e93f-7c26-4cb6-9b03-73cedc1a5dad.jpg)
      
      You are also allowed to change the default topological structure of the program to reshape different solids or make more holes in the “main” source file if not satisfied with simple hexahedron. But be advised that this behavior is highly dangerous as you might create incorrect topological structures that MeshFramework cannot load. So far, this program does not support for generating multiple solids.
      
      ![0d27d0846dff60bf098a0a3a51f5ad0](https://user-images.githubusercontent.com/86988075/200839684-9feba3a2-3371-4353-b698-5414f451fdb9.jpg)
      
#Reference
1. Prof. Gao. Lecture notes (2022), 3-D CAD Modeling. Zhejiang University.
2. Mäntylä M. An introduction to solid modeling[M]. Computer Science Press, Inc., 1987.
3. Shah J J, Mäntylä M. Parametric and feature-based CAD/CAM: concepts, techniques, and applications[M]. John Wiley & Sons, 1995.
4. 唐荣锡, 汪嘉业, 彭群生. 计算机图形学教程[J]. 北京: 科学出版杜, 1990: 20-75.
      






      
      
      
      



     
     

