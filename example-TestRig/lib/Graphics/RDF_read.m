function [points, connectivity, MU] = RDF_read(filename) 
% Script for importing mesh data from RDF file:
%

file = fileread(filename);
data = regexp(file,['.NODES.|' '.ELEMENTS.'],'split');

if regexp(file,'.NODES.') > regexp(file,'.ELEMENTS.')
    NODE_data = data{3};
    ELEM_data = data{2};
else
    NODE_data = data{2};
    ELEM_data = data{3};
end

fnode_tmp = fopen('./tmp/NODE.rdf','w');
felem_tmp = fopen('./tmp/ELEM.rdf','w');

fprintf(fnode_tmp,NODE_data);
fprintf(felem_tmp,ELEM_data);

fclose(fnode_tmp);
fclose(felem_tmp);

%% NODES
optsN = delimitedTextImportOptions("NumVariables", 4);
% Specify range and delimiter
optsN.DataLines = [3, Inf];
optsN.Delimiter = " ";
% Specify column names and types
optsN.VariableNames = ["id", "x_coord", "y_coord", "z_coord"];
optsN.SelectedVariableNames = ["id", "x_coord", "y_coord", "z_coord"];
optsN.VariableTypes = ["uint16", "double", "double", "double"];
optsN.ExtraColumnsRule = "ignore";
optsN.ConsecutiveDelimitersRule = "join";
optsN.LeadingDelimitersRule = "ignore";
% Import the data
p_temp = readtable('./tmp/NODE.rdf', optsN);
startfromzero = 1 - min(p_temp.id);
M_id = max(p_temp.id)+startfromzero;
points = zeros(M_id,3);
for i=p_temp.id
    points(i+startfromzero,:)= [p_temp.x_coord(p_temp.id==i) p_temp.y_coord(p_temp.id==i) p_temp.z_coord(p_temp.id==i)];  % i+1 cause id in NODES starts from 0 but not in ELEMENTS!!
end

%% ELEMENTS
optsE = delimitedTextImportOptions("NumVariables", 4);
% Specify range and delimiter
optsE.DataLines = [3, Inf];
optsE.Delimiter = " ";
% Specify column names and types
optsE.VariableNames = ["n1", "n2", "n3", "mu"];
optsE.SelectedVariableNames = ["n1", "n2", "n3", "mu"];
optsE.VariableTypes = ["double", "double", "double", "double"];
optsE.ExtraColumnsRule = "ignore";
optsE.ConsecutiveDelimitersRule = "join";
optsE.LeadingDelimitersRule = "ignore";
% Import the data
c_temp = table2array(readtable('./tmp/ELEM.rdf', optsE));
connectivity = c_temp(:,1:3);
MU = c_temp(:,4);

%% Clear temporary variables and files
clear optsN; clear optsE; clear p_temp; clear M_id; clear c_temp;
delete './tmp/NODE.rdf' './tmp/ELEM.rdf'