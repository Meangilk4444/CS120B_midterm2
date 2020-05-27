
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i

/* complete the state machine. */
static unsigned amp = 0x00;
static unsigned i = 0x00;
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
	    	if((amp != 0) && amp > temp)
		{
			temp = amp;
			detect_max_amp_state = M;
		}
		else if(amp == 0)
		{
			detect_max_amp_state = Wait;
		}
		break;

	 case Wait:
		if(amp == 0)
		{
			i++;
			detect_max_amp_state = Wait;
		}
		else if(amp != 0)
		{
			detect_max_amp_state = M;
		}

		if(i >= 10)
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
		i = 0x00;
		temp = 0x00;
            break;

	case M:
	    max_led = temp;
	    i = 0x00;
	    break;
        default:
            break;
    }
}
