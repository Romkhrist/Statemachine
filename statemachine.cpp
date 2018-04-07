#include <iostream>
#include <fstream>

int main(int argc, char*argv[])
{
    std::ifstream fin;
    std::ofstream fout;
	
	enum class state
	{
		DEFAULT,             // Basic state
		DEFAULT_SLASH,       // State after '/' in basic state
		SLASHSLASH,          // Such comment as "//this is the C++-style comment"
		SLASHSTAR,           // Such comment as "//this is the C-style comment"
		SLASHSTAR_STAR,      // State after '*' in SLASH_STAR state   
		SINGLEQUOTES,        // State after "'" in DEFAULT state
		SINGLEQUOTES_SLASH,  // State after "/" in SINGLEQUOTES state
		DOUBLEQUOTES,        // State after '"' in DEFAULT state
	};
		
	if(argc == 1)
	{
		printf(" ->ERROR: input file wasn't specified!\n");
		return 1;
	}
	else if(argc == 2)
	{
		std::cout << " ->ERROR: output file wasn't specified!\n";
		return 1;
	}
	else if(argc > 3)
	{
		std::cout << " ->ERROR: too many parameters!\n";
		return 1;
	}
	
	fin.open(argv[1], std::ios_base::in);
	if(!fin)
	{
	    std::cout << " ->ERROR: input file doesn't exist!\n";
		return 1;
	}
	
	fout.open(argv[2]);
	if(!fout)
	{
	    std::cout << " ->ERROR: output file doesn't exist!\n";
		fin.close();
		return 1;
	}
	
	state s = state::DEFAULT;
	
	while(true)
	{
	    char c;
	    fin.get(c);
	    if(fin.eof())
	    {
	        if(s == state::DEFAULT_SLASH || s == state::SINGLEQUOTES_SLASH)
	        {
	            fout.put('/');
	        }
	        
	        break;
	    }
	    
		switch(s)
		{
			case state::DEFAULT:
			    switch(c)
			    {
			        case '/':
			            s = state::DEFAULT_SLASH;
			            break;
			        case '\'':
			            s = state::SINGLEQUOTES;
			            fout.put(c);
			            break; 
			        case '"':
			            s = state::DOUBLEQUOTES;
			            fout.put(c);
			            break;
			        default:
			            fout.put(c);
			    }      
			    break;
			case state::DEFAULT_SLASH:
			    switch(c)
			    {
			        case '/':
			            s = state::SLASHSLASH;
			            break;
			        case '*':
			            s = state::SLASHSTAR;
			            break;
			        default:
			            fout.put('/');
			            fout.put(c);
			    }
			    break;
            case state::SLASHSLASH:
		        switch(c)
		        {
		            case '\n':
		                s = state::DEFAULT;
		                fout.put(c);
		        }
		        break;
		    case state::SLASHSTAR:
		        switch(c)
		        {
		            case '*':
		                s = state::SLASHSTAR_STAR;
		        }
		        break;
		    case state::SLASHSTAR_STAR:
		        switch(c)
		        {
		            case '/':
		                s = state::DEFAULT;
		        }
		        break;
		    case state::SINGLEQUOTES:
		        switch(c)
		        {
		            case '\'':
		            case '\n':
		                s = state::DEFAULT;
		                fout.put(c);
		                break;
		            case '/':
		                s = state::SINGLEQUOTES_SLASH;
		                break;
		            default:
		                fout.put(c);
		        }
		        break;
		    case state::SINGLEQUOTES_SLASH:
		        switch(c)
		        {
		            case '\'':
		            case '\n':
		                s = state::DEFAULT;
		                fout.put('/');
		                fout.put(c);
		                break;
		            case '/':
		                s = state::SLASHSLASH;
		                break;
		            case '*':
		                s = state::SLASHSTAR;
		                break;
		            default:
		                fout.put('/');
		                fout.put(c);
		        }
		        break;		       
		    case state::DOUBLEQUOTES:
		        switch(c)
		        {
		            case '"':
		            case '\n':
		                s = state::DEFAULT;
		                fout.put(c);
		                break;
		            default:
		                fout.put(c);
		        }
		}			
	}
	
	fin.close();
	fout.close();
	return 0;
}
