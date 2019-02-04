procedure test is

	v : Integer;

begin 

	v := 3;

	case v is
		when 1 => Put("a");
		when 2 => Put("b");
		when others => Put("c");
	end case;

end ;
