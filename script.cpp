resize(matched_properties,0);//creating arrays for attempting to find matches of incoming values to current
resize(matched_value,0);
resize(unmatched_properties,0);
resize(unmatched_old_value,0);
resize(unmatched_new_value,0);

for #i in 1 .. numproperties()-5 //the minus 5 removes the created properties above from the loop
loop
    if arraynumvalues(ithproperty(#i)) > 1 then//cycling through an array of values, if present. Previously, incoming values and current values were merged into an array, if they existed
    if ithproperty(#i)[1] = ithproperty(#i)[2] and ithproperty(#i) ne 'null' then//The merge was successful, and the property is defined in the new data and current DB, and the values are the same
        append(matched_properties,ithpropertyname(#i));//alter the created array to show a property name matched
        append(matched_value,ithproperty(#i)[1]);//alter the created array to show the value of the matched property
    elsif ithproperty(#i)[1] ne 'null' or ithproperty(#i)[2] ne 'null' then//The property is present in incoming data and the DB, but with different values
        append(unmatched_properties,ithpropertyname(#i));//Because they're different values, append the properties to being unmatched
        append(unmatched_old_value,ithproperty(#i)[2]);//track the incoming and current values of the property, respectively
        append(unmatched_new_value,ithproperty(#i)[1]);
    end if;
    end if;
end loop;
Property('Number_Matches'):=arraynumvalues(matched_properties);//How many properties ended up matching and (below) not?
Property('Number_Non_Matches'):=arraynumvalues(unmatched_properties);

Calculating starting values of SARS viral particles in a qPCR sample:
SARS_Average_SQ := "NA";//SQ meaning starting quantity of measured gene for SARS virus
numerator := 0;
denominator := 0;

for #i in 1 .. ArrayNumvalues(SARS_Starting_Quantity)//Looping based on technical replicates on the qPCR plate
    loop
    if SARS_Starting_Quantity[#i] ne "" and SARS_Starting_Quantity[#i] != 0 then//Starting quantity was calculated and is a non-zero number
        numerator := SARS_Starting_Quantity[#i] + numerator;//increase numerator value
        denominator := denominator + 1;//iterate denominator
    end if;
end loop;

if denominator > 0 then
    SARS_Average_SQ := numerator/denominator;//if capable, calculate the average from the updated numerator and denominators
end if;
sample_keep := "Yes";//this particular program brings in lots more data than what's actually used; later on the sample_keep is used to filter unwanted ones out
