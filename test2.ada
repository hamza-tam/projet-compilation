procedure remplir_tableau is
	
	x : Integer;

	procedure rec is

	begin 
		if x < 5 then 
			Put(x);
			x := x + 1;
			rec;
		end if;
	end;

begin 

	x := 0;

	rec;

end;
