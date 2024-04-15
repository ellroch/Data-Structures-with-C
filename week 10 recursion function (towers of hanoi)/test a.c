int movestack(unsigned int DiskNumber, Diskptr *peg, unsigned int long pegCycle){
	Diskptr hold;
	unsigned int long thisMove;
	unsigned int long otherMoves;
	int pegKey= pegCycle%3; 
	
//--------------------------------------------------------------------------------------------------- move disk

	if (((peg[pegKey])->count)%2==0){// stack has even number of disks	
		if (pegKey==0){
			if (((peg[pegKey]->size)<(peg[1]->size)) || peg[1]==NULL){ //move to peg_B
			
				hold= peg[pegKey];
				peg[pegKey]= (peg[pegKey])->next;
				if (peg[1]==NULL){
					hold->count=1;
				}
				else {
					hold->count= (peg[1]->count)+1;
				}
				hold->next= peg[1];
				peg[1]= hold;
				thisMove=1;
			}
			else{
				pegCycle++;
				thisMove=0;
			}
		}
		else{
			if (((peg[pegKey]->size)<(peg[0]->size)) || peg[0]==NULL){ //move to peg_A
				
				hold= peg[pegKey];
				peg[pegKey]= (peg[pegKey])->next;
				if (peg[0]==NULL){
					hold->count=1;
				}
				else {
					hold->count= (peg[0]->count)+1;
				}
				hold->next= peg[0];
				peg[0]= hold;
				thisMove=1;
			}
			else {
				pegCycle++;
				thisMove=0;
			}
		}
	}
		else {// stack has odd number of disks
			if (pegKey==2){
				if (((peg[pegKey]->size)<(peg[1]->size)) || peg[1]==NULL){ //move to peg_B
					
					hold= peg[pegKey];
					peg[pegKey]= (peg[pegKey])->next;
					if (peg[1]==NULL){
						hold->count=1;
					}	
					else {
						hold->count= (peg[1]->count)+1;
					}
					hold->next= peg[1];
					peg[1]= hold;
					thisMove=1;
				}
				else{
					pegCycle++;
					thisMove=0;
				}
			}
			else {
				if (((peg[pegKey]->size)<(peg[2]->size)) || peg[2]==NULL){ //move to peg_C
					
					hold= peg[pegKey];
					peg[pegKey]= (peg[pegKey])->next;
					if (peg[2]==NULL){
						hold->count=1;
					}
					else {
						hold->count= (peg[2]->count)+1;
					}
					hold->next= peg[2];
					peg[2]= hold;
					thisMove=1;
				}
				else {
					pegCycle++;
					thisMove=0;
				}
			}
		}
//--------------------------------------------------------------------------------------------------- determine if to call again
	if ((peg[pegKey]->count)==DiskNumber) {
		otherMoves= movestack(DiskNumber, &peg[0], pegCycle);
	}
	else {
		otherMoves=0;
	}
//--------------------------------------------------------------------------------------------------- return
	return (thisMove+otherMoves);
	
	}
	
	
	