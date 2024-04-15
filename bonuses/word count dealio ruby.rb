puts"file path to count words for:" # delete this chunk
f_name= gets.chomp

text=File.read(f_name)

words= text.split
frequencies= Hash.new(0)
words.each{ |word| frequencies[word]+=1 }

frequencies= frequencies.sort_by{ |word, count| count }

frequencies.reverse!
frequencies.each{ |word, count| 
    puts word + " " + count.to_s }
	
	
	
# The source I used for making this in ruby are almost entirely from codecademy, 
# they have a ruby course which includes the making of a wordcount histogram similar to this... 
# coincidentally i paused my progress right before that lesson--- i picked it back up since it fit the bill so nicely.
# idk if this is link is unique to the account or if its openly available but the course is here
# <https://www.codecademy.com/learn/ruby --- the particular lesson is unit 4 lesson 2, making a histogram---
# one of the advisors from the site said that this would take 20-30 lines in python at most, 
# and i imagined C would be longer so yea :D
	