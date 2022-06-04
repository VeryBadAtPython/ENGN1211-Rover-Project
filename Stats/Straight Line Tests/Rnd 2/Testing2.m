inData = readtable('Testing2.csv');
data   = inData{:,:};

% Data for polar plot C1=Radial Disp C2=Angle
polarData   = data(2:11,5:6);
polarMean   = data(12,5:6);
polarMedian = data(13,5:6);
polarTarget = data(1,5:6);
polarStdDev = data(14,5:6);

muT    = polarMean(1,2);
sigmaT = polarStdDev(1,2);

muD    = polarMean(1,1);
sigmaD = polarStdDev(1,1);

% Data for cartesian plot C1=xDisp Disp C2=yDisp
xyData   = data(2:11,2:3);
xyMean   = data(12,2:3);
xyMedian = data(13,2:3);
xyTarget = data(1,2:3);
xyStdDev = data(14,2:3);

%Plots
tiledlayout(1,2);

%Dist of dist travelled
nexttile;
xD = ((muD-5*sigmaD):0.01:(muD+5*sigmaD));
pD = normpdf(xD,muD,sigmaD);
dists = polarData(1:10,1);
ys = 0*dists;
plot(xD,pD);
hold on;
scatter(dists,ys,'black')
grid on;
xticks([240 245 250 255 260 265 270])
xlabel('Distance Travelled (mm) Target 250mm');
ylabel('Probability Density');
title('Distance Travelled','FontSize',12);

%Scatter
nexttile;
plot([0,300],[0,0],'black');
hold on;
scatter(xyData(1:10,1),xyData(1:10,2),'black',"filled");
hold on;
scatter(xyTarget(1,1),xyTarget(1,2),'red',"filled");
hold on;
scatter(xyMean(1,1),xyMean(1,2),'blue',"filled")
hold on;
scatter(xyMedian(1,1),xyMedian(1,2),'green',"filled")
grid on;
box on;
axis ([0 300 -15 45]);
xlabel('Distance Traveled (mm)');
ylabel('Deviation (mm)');
title('250mm Line Finishing positions','FontSize',12);
legend ({'0 Deviation','Measured','Target','Mean','Median'});