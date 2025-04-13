#include "motors.h"

double absolute(double speed){
	if(speed < 0) return speed * -1;
	else return speed;
}
double min(double speed){
	if(speed < 0) return 0;
	else return speed;
}

void speed(double h_offset, double speed, int crab){
	double leftSpeed = 0;
	if (absolute(speed)== 0){
	}else if(absolute(speed) == 1){
		leftSpeed = LOW;
	}else if(absolute(speed) == 2){
		leftSpeed = MED;
	}else{
		leftSpeed = HIGH;
	}
	double rightSpeed = leftSpeed;
	double h_displacement = absolute(h_offset);
	double new_gain = ((10000.0 / 3.0) * absolute(speed)) / 3.0 * GAIN;
	if(!(crab == 1 && h_offset != 0)){
		if(h_offset < 0){
			rightSpeed -= h_displacement * new_gain;
		} else if (h_offset == 0 && speed > 0){
			leftSpeed -= 200;
		}else {
			leftSpeed -= h_displacement * new_gain;
		}
		if(h_offset == 3 || h_offset == -3){
			if (speed > 0){
				if(h_offset < 0){
					TPM1_C0V = 0; 
					TPM1_C1V = min(leftSpeed);
					TPM2_C0V = BRAKE;
					TPM2_C1V = 0; 
				} else {
					TPM1_C0V = BRAKE;
					TPM1_C1V = 0;
					TPM2_C0V = 0;
					TPM2_C1V = min(rightSpeed);
				}
			} else{
				if(h_offset < 0){
					TPM1_C0V = min(leftSpeed);
					TPM1_C1V = 0;
					TPM2_C0V = 0;
					TPM2_C1V = BRAKE;
					
				} else {
					TPM1_C0V = 0;
					TPM1_C1V = BRAKE;
					TPM2_C0V = min(rightSpeed);
					TPM2_C1V = 0;
				}
			}
		}else {
		if(speed > 0){
			TPM1_C0V = 0;
			TPM1_C1V = min(leftSpeed);
			TPM2_C0V = 0;
			TPM2_C1V = min(rightSpeed);
		} else {
			TPM1_C0V = min(leftSpeed);
			TPM1_C1V = 0;
			TPM2_C0V = min(rightSpeed);
			TPM2_C1V = 0;
		}
	}
}else{
	if(h_offset > 0){
			TPM1_C0V = 0;
			TPM1_C1V = LOW;
			TPM2_C0V = LOW;
			TPM2_C1V = 0;
		} else {
			TPM1_C0V = LOW;
			TPM1_C1V = 0;
			TPM2_C0V = 0;
			TPM2_C1V = LOW;
		}
}
}

void initPWM(void){
	// Enable clock for Port B
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;

	// Set PTB0, PTB1 for TPM1 (Left Motor)
	PORTB->PCR[PTB0_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[PTB0_Pin] |= PORT_PCR_MUX(3);
	PORTB->PCR[PTB1_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[PTB1_Pin] |= PORT_PCR_MUX(3);

	// Enable TPM1 clock
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;

	// Set TPM clock source
	SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);

	TPM1->MOD = 7500;
	TPM1->SC &= ~(TPM_SC_CMOD_MASK | TPM_SC_PS_MASK);
	TPM1->SC |= TPM_SC_CMOD(1) | TPM_SC_PS(7);
	TPM1->SC &= ~TPM_SC_CPWMS_MASK;

	TPM1_C0SC &= ~(TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_MSA_MASK);
	TPM1_C0SC |= TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1);

	TPM1_C1SC &= ~(TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_MSA_MASK);
	TPM1_C1SC |= TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1);

	// Set PTB2, PTB3 for TPM2 (Right Motor)
	PORTB->PCR[PTB2_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[PTB2_Pin] |= PORT_PCR_MUX(3);
	PORTB->PCR[PTB3_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[PTB3_Pin] |= PORT_PCR_MUX(3);

	// Enable TPM2 clock
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;

	TPM2->MOD = 7500;
	TPM2->SC &= ~(TPM_SC_CMOD_MASK | TPM_SC_PS_MASK);
	TPM2->SC |= TPM_SC_CMOD(1) | TPM_SC_PS(7);
	TPM2->SC &= ~TPM_SC_CPWMS_MASK;

	TPM2_C0SC &= ~(TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_MSA_MASK);
	TPM2_C0SC |= TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1);

	TPM2_C1SC &= ~(TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_MSA_MASK);
	TPM2_C1SC |= TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1);
}
