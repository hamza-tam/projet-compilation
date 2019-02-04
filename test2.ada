	
procedure main is

	c : Integer;

	procedure test_recursivite is
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


	procedure test_tableau is
		i : Integer;
		a : array(2 .. 5) of Integer;
	begin
		Put("Saisi du tableau");
		Put('\n');
		
		-- Saisi
		i:=2;
		while i <= 5 loop
			Get(a(i));
			i:=i+1;
		end;


		-- affichage
		i:=2;
		while i <= 5 loop
			Put(a(i));
			Put(" | ");
			i:=i+1;
		end;
		Put('\n');
	end;

begin
	loop
		Put("Choisissez une option : ");
		Put('\n');
		Put("[1] Pour le test de la recursivite");
		Put('\n');
		Put("[2] Pour le test du tableau");
		Put('\n');
		Put("Choix : ");

		Get(c);

		case c is
			when 1  => test_recursivite;
			when 2  => test_tableau;
			when others => c := 0;
		end;

		exit when c = 0;
	end loop;
end;


