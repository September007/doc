import numpy as np
import matplotlib.pyplot as plt

nRow = 8
nCol = 8
nFreqHoriz = 8
nFreqVerti = 8
normFreqDC = 1/np.sqrt(2)

for iFreqH in range(nFreqHoriz):
    for iFreqV in range(nFreqVerti):
        iFreqHoriz = iFreqH
        iFreqVerti = iFreqV
        matFreq2D = np.zeros((nRow,nCol))
        for iRow in range(nRow):
            for iCol in range(nCol):
                iRow0 = iRow
                iCol0 = iCol
                matFreq2D[iRow,iCol] = 2/(np.sqrt(nFreqHoriz)*np.sqrt(nFreqVerti))*np.cos(np.pi*iFreqHoriz*(2*iRow0+1)/(2*nRow))*np.cos(np.pi*iFreqVerti*(2*iCol0+1)/(2*nCol))
                if iFreqHoriz == 0:
                    matFreq2D[iRow,iCol] =  matFreq2D[iRow,iCol]*normFreqDC
                if iFreqVerti == 0:
                    matFreq2D[iRow,iCol] =  matFreq2D[iRow,iCol]*normFreqDC
        print(np.sum(matFreq2D**2))
        plt.subplot(nFreqHoriz,nFreqVerti,8*iFreqV+iFreqH+1)
        plt.imshow(matFreq2D, cmap='gray')
        plt.axis('off')
plt.show()
