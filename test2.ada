procedure main is

	v:Character := 'c';
	c:Integer;

	procedure to_char is 
		a : Character;
	begin
		Get(a;
		Put(a);
		Put('\n');
	end;


begin 

	v:=2-3;
	--if v=2 then v:=3;
	--elsif v=29 then v:=5;	
	--elsif v=27 then v:=12;	
	--elsif v=23 then v:=11;	
	--elsif v=24 then v:=18;
	--else v:=8;
	--end if;

		Get(c);
		
		if c = 1 then to_char;
		end if;

		exit when c = 0;
	end loop;

end;

