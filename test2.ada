procedure test is

	v : Integer;
	a : Integer;

	procedure test2 is 
	begin 
		Put("hello");
	end;

begin 

	case v is
		when 1 => test;
		when 2 => test;
	end case;

end ;
