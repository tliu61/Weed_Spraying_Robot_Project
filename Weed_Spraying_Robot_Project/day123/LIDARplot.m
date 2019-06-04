%%
clc
clear
data = load('day123.txt.txt');
index = data(:,1);
dist = data(:,2);

plot(dist(1:228),dist(229:456),'.')






