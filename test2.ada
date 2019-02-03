procedure main is

	v:Character := 'c';
	c:Integer;

	procedure to_char is 
		a : Character;
	begin
		Get(a);
		Put(a);
		Put('\n');
	end;

begin 

	Put("Bienvenue");
	Put('\n');
	Put('\n');
	Put("1 - Transformer en charactere");
	Put('\n');
	Put("0 - quitter");
	Put('\n');

	loop

		Get(c);
		
		if c = 1 then to_char;

		exit when c = 0;
	end loop;

end;