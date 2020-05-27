
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i



/*complete the state machine*/
static unsigned char L = 0x00;
static unsigned char H = 0x00;
static unsigned char i = 0x00;

void Ping()
{
    switch(ping_state)
    {
        case PInit:
            break;

	case HIGH:
	    if( i <= H)
	    {
		    ping_state = HIGH;
	    }
	    else
	    {
		    i = 0;
		    ping_state = LOW;
	    }
		break;

	case LOW:
		if(i <= L)
		{
			ping_state = LOW;
		}
		else
		{
			i = 0;
			ping_state = HIGH;
		}
		break;
        default:
            ping_state = PInit;
            break;
    }
    switch(ping_state)
    {
        case PInit:
		ping_led = 0x00;
		L = 9;
		H = 1;
            break;

	case HIGH: 
	    i++;
	    ping_led = 0x01;
		break;
	case LOW:
	    i++;
	    ping_led = 0x00;
    	break;
        default:
            break;
    }
}
