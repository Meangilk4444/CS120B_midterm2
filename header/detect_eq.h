//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i


static unsigned char amp = 0x00;
static unsigned char i = 0x00;
/*complete the state machine*/

void Detect_EQ()
{
	amp = ~PINA & 0xF8;
    switch(detect_eq_state)
    {
        case DEQInit:
            //init variable(s) here.
	    if(amp > 0)
	    {
		    detect_eq_state = ON;

	    }
	    else
	    {
		    detect_eq_state = DEQInit;
	    }
            break;

	case ON:
	    if(amp != 0)
	    {
		    detect_eq_state = ON;
	    }
	    else
	    {
		    detect_eq_state = WAIT;
	    }
	    break;

	  case WAIT:
	    if(amp == 0)
	    {	
		    i++;
		    detect_eq_state = WAIT;
	    }
	    else if(amp != 0)
	    {
		detect_eq_state = ON;
	    }
	    else
	    {
	    }

	    if(i >= 10)
	    {
		    i = 0;
		    detect_eq_state = DEQInit;
	    }
	    break;

	    
        default:
            detect_eq_state = DEQInit;
            break;
    }
    switch(detect_eq_state)
    {
        case DEQInit:
		i = 0x00;
		eq_led = 0x00;
            break;
	case ON: 
	    i = 0x00;
	    eq_led = 0x02;
	    break;
        default:
            break;
    }
}
