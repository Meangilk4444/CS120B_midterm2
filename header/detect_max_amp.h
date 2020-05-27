
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i

/* complete the state machine. */
static unsigned max = 0x00;
static unsigned j = 0x00;
static unsigned temp = 0x00;
void Detect_Max_Amp()
{
	amp  = ~PINA & 0xF8;
    switch(detect_max_amp_state)
    {
        case DMAInit:
		if(amp > 0)
		{
			detect_max_amp_state = M;
		}
		else
		{
			detect_max_amp_state = DMAInit;
		}
            break;

	 case M:
	    	if((max != 0) && amp > temp)
		{
			temp = amp;
			detect_max_amp_state = M;
		}
		else if(max == 0)
		{
			detect_max_amp_state = Wait;
		}
		break;

	 case Wait:
		if(max == 0)
		{
			j++;
			detect_max_amp_state = Wait;
		}
		else if(max != 0)
		{
			detect_max_amp_state = M;
		}

		if(j >= 10)
		{
			detect_max_amp_state = DMAInit;
		}
		break;
        
        default:
            break;
    }
    switch(detect_max_amp_state)
    {
        case DMAInit:
		j = 0x00;
		temp = 0x00;
            break;

	case M:
	    max_led = temp;
	    j = 0x00;
	    break;
        default:
            break;
    }
}
