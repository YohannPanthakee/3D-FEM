import matplotlib.pyplot as plt
import math
import pandas as pd
import numpy as np
import time
import os
from datetime import datetime
from Augmentation import Data_Augment
import xlsxwriter

start_time = time.time()

#--------------------------------
# Calling the Class Data_augment
#--------------------------------
augment = Data_Augment()

#-------------------------------------
# Function to build the global matrix
#-------------------------------------

def enlarged_matrix(matrix,loc,size):
    zero_matrix = np.zeros((size,size))
    for n in range(size): # iterate over rows of big matrix
        for m in range(size): # iterate over cols of big matrix
            for i, a in enumerate(loc): # iterate over rows of small matrix
                for j, b in enumerate(loc): # iterate over cols of small matrix
                    if [n,m] == [a-1,b-1]:
                        zero_matrix[n,m] = matrix[i,j]
    return zero_matrix

#--------------
# The file name
#--------------
file = "Truss Config 3D"
sheet_name = "Example"

#------------------------------------------------------------------------
# Generate the path to parse into the excel import as a pandas Data frame
#------------------------------------------------------------------------
path = f"{os.getcwd()}/{file}.xlsx"


Truss_Dataframe = pd.read_excel(pd.ExcelFile(path), sheet_name)

#---------------------------------------------------------------------------------------------
# Split the dataframe into sub frames and remove the NaN values and convert to a list of lists
#---------------------------------------------------------------------------------------------
supports = Truss_Dataframe.loc[:, ['Support X', 'Support Y','Support Z']].dropna().values.tolist()
loads = Truss_Dataframe.loc[:, ['Load X', 'Load Y','Load Z']].dropna().values.tolist()
DoF = Truss_Dataframe.loc[:, ['DoF 1','DoF 2','DoF 3','DoF 4','DoF 5','DoF 6']].dropna().values.tolist()
ymod = Truss_Dataframe.loc[:, ['Youngs Modulus']].dropna().round(0).astype(int).values.tolist()
cross_area = Truss_Dataframe.loc[:, ['Cross Sectional Area']].dropna().values.tolist()

coordinates = Truss_Dataframe.loc[:, ['Coord X', 'Coord Y','Coord Z']].dropna().values.tolist()
coordx, coordy, coordz = augment.split3(coordinates)

connections = Truss_Dataframe.loc[:, ['Connect 1', 'Connect 2']].dropna().round(0).astype(int).values.tolist()
elements, connection1, connection2 = augment.sub1_split(connections)

cross_area = augment.flatten(cross_area)
ymod = augment.flatten(ymod)
loads = augment.flatten(loads)
supports = augment.flatten(supports)

fixed_Dof = []
free_Dof = []

for i, ii in enumerate(supports):
    if ii == 1:
        fixed_Dof.append(i)

for i, ii in enumerate(supports):
    if ii != 1:
        free_Dof.append(i)

print(loads)


#---------------------------------------------------------------------------------------------------------------
# Calculating the lengths of each of the elements and calculating the Local & seperate global Stiffness matrixes
#---------------------------------------------------------------------------------------------------------------
seperate_global_matrix = []
seperate_local_matrix = []
stress_constant = []
stress_matrix = []
force_matrix = []

lengths = []
angle_comp = []


for i in range(len(elements)):

    n1 = connection1[i]
    n2 = connection2[i]

    x1 = coordx[n1-1] # extracts the x coordinates for the first node
    y1 = coordy[n1-1] # extracts the y coordinates for the first node
    z1 = coordz[n1-1] # extracts the z coordinates for the first node

    x2 = coordx[n2-1] # extracts the x coordinates for the second node
    y2 = coordy[n2-1] # extracts the y coordinates for the second node
    z2 = coordz[n2-1] # extracts the z coordinates for the second node

    deltaX = x2-x1 # calculates the change in the x plane
    deltaY = y2-y1 # calculates the change in the y plane
    deltaZ = z2-z1 # calculates the change in the z plane

    length = math.sqrt((deltaX)**2 + (deltaY)**2 + (deltaZ)**2) # calculates the length of the element

    lengths.append(length)

    mat_constant = (ymod[i]*cross_area[i])/length # calculates the material constatant of the element
    mat_constant2 = ymod[i]/length # calculates the stress material constatant of the element

    Cx = (deltaX/length) # calculates the angle of the element in the x plane ≡ cos(theta)x
    Cy = (deltaY/length) # calculates the angle of the element in the y plane ≡ cos(theta)y
    Cz = (deltaZ/length) # calculates the angle of the element in the z plane ≡ cos(theta)z

    angle_comp.append([Cx,Cy,Cz])

    # only 3 variables are needed "Cxy Cxz Cyz"
    Cxy = Cx * Cy   # calculates the material Cxy variable
    Cxz = Cx * Cz   # calculates the material Cxz variable
    Cyz = Cy * Cz   # calculates the material Cyz variable

    local = np.array([[    Cx**2 ,    Cxy   ,    Cxz   , -1*Cx**2 , -1*Cxy   , -1*Cxz   ],
                      [    Cxy   ,    Cy**2 ,    Cyz   , -1*Cxy   , -1*Cy**2 , -1*Cyz   ],
                      [    Cxz   ,    Cyz   ,    Cz**2 , -1*Cxz   , -1*Cyz   , -1*Cz**2 ],
                      [ -1*Cx**2 , -1*Cxy   , -1*Cxz   ,    Cx**2 ,    Cxy   ,    Cxz   ],
                      [ -1*Cxy   , -1*Cy**2 , -1*Cyz   ,    Cxy   ,    Cy**2 ,    Cyz   ],
                      [ -1*Cxz   , -1*Cyz   , -1*Cz**2 ,    Cxz   ,    Cyz   ,    Cz**2 ]]) * mat_constant

    EL = np.array([[-1*Cx,-1*Cy,-1*Cz,Cx,Cy,Cz]])*mat_constant2

    EAL = np.array([[-1*Cx,-1*Cy,-1*Cz,Cx,Cy,Cz],
                      [Cx,Cy,Cz,-1*Cx,-1*Cy,-1*Cz]])*mat_constant

    enlarged = enlarged_matrix(local,DoF[i],len(coordinates)*3) # calculates a global matrix for each of the elements seperatly

    seperate_global_matrix.append(enlarged) # add each global matrix to a list of lists
    seperate_local_matrix.append(local) # add each local matrix to a list of lists

    stress_constant.append(mat_constant2)
    stress_matrix.append(EL)
    force_matrix.append(EAL)

#------------------------------------------------------------------------------
# Genrating the final Global Stiffness Matrix
#------------------------------------------------------------------------------

Global_matrix = sum(seperate_global_matrix) # add all of the sepertate global matrixes to make the final global matrix

#----------------
# Row elimination
#----------------

global_df = pd.DataFrame(Global_matrix) # converted to a pandas dataframe as it is easier for row elimination
loads_df = pd.DataFrame(loads) # converted to a pandas dataframe as it is easier for row elimination

reduced_global = augment.elimination(global_df,fixed_Dof) # row & colum elimination for the global matrix
reduced_loads = loads_df.drop(fixed_Dof, axis = 0) # row elimination for the force vector

# convert back into a numpy array for rest of calculations
reduced_global = reduced_global.to_numpy()
reduced_loads = reduced_loads.to_numpy()
original_Global = global_df.to_numpy()

#-------------------------------
# Calculating Displacment Vector
#-------------------------------

Displacments = np.dot(np.linalg.inv(reduced_global),reduced_loads) # calculates the displacemnt vector by "inv(reduced_global) * reduced_force"

#-----------------------------
# Calculating the Force Vector
#-----------------------------

Full_Displacement = np.zeros((len(coordinates)*3)) # create a new blank vector for all the displacments

np.put(Full_Displacement, free_Dof, Displacments) # insert the calculated displacment values back into the vector in the positions of free_Dof

Forces = np.dot(original_Global,Full_Displacement) # calcualte the full force vector by "original_Global * new displacemnt"

DX = [Full_Displacement[i] for i in list(range(0,len(Full_Displacement),3))]
DY = [Full_Displacement[i] for i in list(range(1,len(Full_Displacement),3))]
DZ = [Full_Displacement[i] for i in list(range(2,len(Full_Displacement)+1,3))]

Resultants = []

for i,ii,iii in zip(DX,DY,DZ):
    Resultants.append(np.sqrt(i**2 + ii**2 + iii**2))

#-----------------------------------------------------------
# Calculating the elemental Forces and Stresses
#-----------------------------------------------------------

ordered_displacment = []

Dof_1, Dof_2, Dof_3, Dof_4, Dof_5, Dof_6 = augment.split6(DoF) # split the Dof imported data into lists of each colums i.e 6 colums therfore 4 lists

for A,B,C,D,E,F in zip(Dof_1, Dof_2, Dof_3, Dof_4, Dof_5, Dof_6):
    ordered_displacment.append([Full_Displacement[A],Full_Displacement[B],Full_Displacement[C],Full_Displacement[D],Full_Displacement[E],Full_Displacement[F]])

axiel_force = []
axiel_state = []
axiel_stress = []

# Calculating the elemetal forces
for i, ii in zip(force_matrix,ordered_displacment):
    force = np.dot(i,ii)

    if abs(force[0]) + force[0] == 0: # check to see if the state is tension adjust the force value "tension"= + & "Compression"= -
        axiel_state.append("Tension")
        axiel_force.append(abs(force[0]))

    elif abs(force[0]) + force[0] != 0:
        axiel_state.append("Compression")
        axiel_force.append(abs(force[0])*-1)

# Calculating the elemetal stresses
for i,ii,iii in zip(stress_matrix,ordered_displacment,axiel_state):
    stress = np.dot(i,ii)

    if iii == "Tension":
        axiel_stress.append(abs(stress[0]))
    elif iii == "Compression":
        axiel_stress.append(abs(stress[0])*-1)

# Generate a pandas datafraame for Export
data1 = {"Nodal Forces (N)": Forces,
        "Nodal Displacment (m)": Full_Displacement,
        }

data2 = {"Force (N)": axiel_force,
        "Stress (Pa)": axiel_stress,
        "State": axiel_state,
        }

Export_DataFrame = pd.DataFrame(data=data1)
Export_DataFrame2 = pd.DataFrame(data=data2)

#-----------------------------------------------------------
# Genrating the visualisation of the 3D spaceframe structure
#-----------------------------------------------------------
scale = 1
deformed = []

ordered_displacment = []
X_new = []
Y_new = []
Z_new = []

for i,ii,iii in zip(range(0,len(coordinates)*3,3),range(1,len(coordinates)*3,3),range(2,len(coordinates)*3,3)):
    X_new.append(Full_Displacement[i])
    Y_new.append(Full_Displacement[ii])
    Z_new.append(Full_Displacement[iii])

for ox, oy, oz, nx, ny, nz in zip(coordx, coordy, coordz, X_new, Y_new, Z_new):
      deformed.append([ox+nx*scale,oy+ny*scale,oz+nz*scale])

# For the 3D graphic Grid
X_Gridscale = max(coordx)/10
Y_Gridscale = max(coordy)/10
Z_Gridoffset = min(coordz)

Grid_structure = [X_Gridscale,Y_Gridscale,Z_Gridoffset]

# For the Deformed 3D Graphic
Deforme_pts = []
for i,ii in zip(connection1,connection2):
    Deforme_pts.append([deformed[i-1],deformed[ii-1]])

Disp_structure = [np.array(Deforme_pts),axiel_state]

# For the Force 3D Graphic
Axiel_max = max(axiel_force)
Axiel_min = min(axiel_force)

Axiel_structure = [Axiel_max,Axiel_min,np.array(axiel_force)]

# For the Stress 3D Graphic
Stress_max = max(axiel_stress)
Stress_min = min(axiel_stress)

Stress_structure = [Stress_max,Stress_min,np.array(axiel_stress)]

#--------------------------------
# Printing Results to the console
#--------------------------------
date = datetime.today()
now = datetime.now()
Axiel_scale = np.linspace(Axiel_min,Axiel_max,5)
Stresses_scale = np.linspace(Stress_min,Stress_max,5)


print("#####----------------------------------------------------#####")
print("##-------------------  3D Truss Solver  --------------------##")
print("#####----------------------------------------------------#####")

print("")
print("Engineer: Yohann")
print("Date: " + date.strftime("%B %d, %Y"))
print("Time: " + now.strftime('%I:%M'))

print("")
print("\033[4mElement State Window Ledgend:\033[0m\n")
print('\x1b[2;30;44m' + '        ' + '\x1b[0m' + " The Elements in {}".format("Tension"))
print('\x1b[2;30;41m' + '        ' + '\x1b[0m' + " The Elements in {}".format("Compression"))

print("")
print("\033[4mAxiel Forces Window Ledgend:\033[0m\n")
print("Units: Kn")
print('\x1b[2;30;41m' + '        ' + '\x1b[0m' + " {}  to {}".format(Axiel_scale[3].round(2),Axiel_max.round(2)))
print('\x1b[2;30;42m' + '        ' + '\x1b[0m' + " {}  to {}".format(Axiel_scale[2].round(2),Axiel_scale[3].round(2)))
print('\x1b[2;30;43m' + '        ' + '\x1b[0m' + " {}  to {}".format(Axiel_scale[1].round(2),Axiel_scale[2].round(2)))
print('\x1b[2;30;44m' + '        ' + '\x1b[0m' + " {}  to {}".format(Axiel_min .round(2),Axiel_scale[1].round(2)))

print("")
print("\033[4mAxiel Stresses Window Ledgend:\033[0m\n")
print("Units: Kn")
print('\x1b[2;30;41m' + '        ' + '\x1b[0m' + " {}  to {}".format(Stresses_scale[3].round(2),Stress_max.round(2)))
print('\x1b[2;30;42m' + '        ' + '\x1b[0m' + " {}  to {}".format(Stresses_scale[2].round(2),Stresses_scale[3].round(2)))
print('\x1b[2;30;43m' + '        ' + '\x1b[0m' + " {}  to {}".format(Stresses_scale[1].round(2),Stresses_scale[2].round(2)))
print('\x1b[2;30;44m' + '        ' + '\x1b[0m' + " {}  to {}".format(Stress_min.round(2),Stresses_scale[1].round(2)))

print("")
print("\033[4mTruss Properties:\033[0m\n")
print("Excel Name: {}.xlsx".format(file))
print("Name: {}".format(sheet_name))
print("Nodes: {}".format(len(coordx)))
print("Elements: {}".format(len(connection1)))
print("DoF: {}".format(len(coordx)*3))
print("Runtime: %.4s seconds" % (time.time() - start_time))

print("")
print(Export_DataFrame)

print("")
print("\033[4mGlobal Matrix:\033[0m\n")
print(global_df.round(2))

print("")
print("\033[4mElemental Axiel Forces and Stresses:\033[0m\n")
print(Export_DataFrame2)

#---------------------------------------------------------
# Export Data To an Excel Spreadsheet for Post Processing
#---------------------------------------------------------

# Create a workbook and add a worksheet
workbook = xlsxwriter.Workbook("Yeet.xlsx")
worksheet = workbook.add_worksheet('Results')
worksheet2 = workbook.add_worksheet('Global matrix')

# Define Data formats
cell_format = workbook.add_format({'bold': True,'align': "Centre","font_size": 12,"bg_color": 'green'})
results_format = workbook.add_format({'bold': True,'align': "Centre","font_size": 12})
global_format = workbook.add_format({'num_format': 11,'align': "Centre"})

# SHEET 1
worksheet.write(0, 0, "Excel Name")
worksheet.write(0, 1, file)

worksheet.write(1, 0, "Project name")
worksheet.write(1, 1, sheet_name)

worksheet.write(2, 0, "Engineer")
worksheet.write(2, 1, "Yohann")

worksheet.write(3, 0, "Date")
worksheet.write(3, 1, date.strftime("%B %d, %Y"))

worksheet.write(4, 0, "Time")
worksheet.write(4, 1, now.strftime('%I:%M'))

for row, (length,disp,force,state) in enumerate(zip(lengths,axiel_force,axiel_stress,axiel_state)):
    worksheet.write(7, 0, "Element ID")
    worksheet.write(7, 1, "Length (M)")
    worksheet.write(7, 2, "Axiel Force (N)")
    worksheet.write(7, 3, "Axiel Stress (Pa)")
    worksheet.write(7, 4, "Axiel State")

    worksheet.write_column(8, 0, range(1,row+2),results_format)
    worksheet.write(row+8, 1,length)
    worksheet.write(row+8, 2,disp)
    worksheet.write(row+8, 3,force)
    worksheet.write(row+8, 4,state)

for row, (disp,force) in enumerate(zip(Full_Displacement,Forces)):
    worksheet.write(7, 6, "Nodal ID")
    worksheet.write(7, 7, "Nodal Displacment (M)")
    worksheet.write(7, 8, "Nodal Force (N)")

    worksheet.write_column(8, 6, range(1,row+2),results_format)
    worksheet.write(row+8, 7,disp)
    worksheet.write(row+8, 8,force)

# SHEET 3
for row, data in enumerate(Global_matrix):
    worksheet2.write_row(0, 1, range(1,row+2),cell_format)
    worksheet2.write_column(1, 0, range(1,row+2),cell_format)
    worksheet2.write_row(row + 1, 1, data,global_format)

workbook.close()

