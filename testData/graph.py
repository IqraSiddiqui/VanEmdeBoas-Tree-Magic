import pandas as pd 
import networkx as nx
import csv
import matplotlib.pyplot as plt
from pyvis.network import Network

df=pd.read_csv("csv_file.csv") #changed it to the github link
net=Network(height='600px',width='500px')
GraphType=nx.Graph()
G=nx.from_pandas_edgelist(df, source='node1', target='node2', edge_attr='distance',create_using=GraphType)
#nx.set_node_attributes(G)
net.from_nx(G)

net.show_buttons(filter_=['interaction'])
net.show("example.html")