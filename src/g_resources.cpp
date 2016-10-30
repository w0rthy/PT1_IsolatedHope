int resource1 = 0;

bool canAfford(int amt){
	return amt <= resource1;
}

void addResource1(int amt){
	resource1 += amt;
}

void deductResource1(int amt){
	resource1 -= amt;
}
