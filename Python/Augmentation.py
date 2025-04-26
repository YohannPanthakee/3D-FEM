import pandas as pd
import numpy as np

class Data_Augment:
	def __init__(self):
		pass

	def sub1_split(self,nested_list):
		"""
		Takes in a nested list and iterates though the list and subtracts 1 from each element
		then using the modified elements builds a new nested list
		@params:
			nested_list - the nested list to be edited (Int)
		"""

		matrix = []
		modified = []
		original = []

		for layer in nested_list:
			for elem in layer:
				new = elem -1
				old = elem
				modified.append(new)
				original.append(old)

		con1 = [modified[i] for i in list(range(0,len(modified),2))]
		con2 = [modified[i] for i in list(range(1,len(modified)+1,2))]

		orig1 = [original[i] for i in list(range(0,len(original),2))]
		orig2 = [original[i] for i in list(range(1,len(original)+1,2))]

		for i,ii in zip(con1,con2):
			matrix.append([i,ii])

		return matrix, orig1, orig2

	def split3(self,nested_list):
		"""
		Takes in a nested list and iterates though the list and subtracts 1 from each element
		then using the modified elements builds a new nested list
		@params:
			nested_list - the nested list to be edited (Int)
		"""
		modified = [item for sublist in nested_list for item in sublist]

		X = [modified[i] for i in list(range(0,len(modified),3))]
		Y = [modified[i] for i in list(range(1,len(modified),3))]
		Z = [modified[i] for i in list(range(2,len(modified)+1,3))]

		return X, Y, Z

	def split6(self,nested_list):
		"""
		Takes in a nested list and iterates though the list and subtracts 1 from each element
		then using the modified elements builds a new nested list
		@params:
			nested_list - the nested list to be edited (Int)
		"""
		modified = []

		for layer in nested_list:
			for elem in layer:
				new = elem - 1

				modified.append(new)

		U = [int(modified[i]) for i in list(range(0,len(modified),6))]
		V = [int(modified[i]) for i in list(range(1,len(modified),6))]
		W = [int(modified[i]) for i in list(range(2,len(modified),6))]
		X = [int(modified[i]) for i in list(range(3,len(modified),6))]
		Y = [int(modified[i]) for i in list(range(4,len(modified),6))]
		Z = [int(modified[i]) for i in list(range(5,len(modified)+1,6))]

		return U, V, W, X, Y, Z


	def flatten(self,list):
		"""
		Takes in a nested list and iterates though the list and subtracts 1 from each element
		then using the modified elements builds a new nested list
		@params:
			nested_list - the nested list to be edited (Int)
		"""
		flatten_List = [item for sublist in list for item in sublist]

		return flatten_List


	def elimination(self,Dataframe,Dof):
		"""
		Takes in a Dataframe of the global matrix and removes the required rows and colums
		@params:
			Dataframe - the nested list to be edited (Int)
		"""
		reduced_row = Dataframe.drop(Dof, axis = 1)
		reduced_col = reduced_row.drop(Dof, axis = 0)

		return reduced_col

	def round(self,num,r_num):
		str = "{:0." + r_num + "e}"
		return str.format(num)
