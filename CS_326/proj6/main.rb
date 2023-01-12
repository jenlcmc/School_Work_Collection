
# Define the Scrabble score for each letter
scores = { 'A' => 1,  'F' => 4,  'K' => 5,  'P' => 3,  'U' => 1,
           'B' => 2,  'G' => 2,  'L' => 1,  'Q' => 10, 'V' => 4,
           'C' => 3,  'H' => 4,  'M' => 3,  'R' => 1,  'W' => 4,
           'D' => 2,  'I' => 1,  'N' => 1,  'S' => 1,  'X' => 8,
           'E' => 1,  'J' => 8,  'O' => 1,  'T' => 1,  'Y' => 4,
           'Z' => 10
         };

#header 
puts "Scrabble Score Calculator"

# Prompt for a word until user quits return with no input
loop do
    #prompt
    print "\n\nEnter word to score: "
    #get input
    word = gets.chomp
    #check to see if end or not
    break if word.empty?
    # Display an error if two or more words are entered
    if word.split.size > 1
        puts "Error, found bad character ' '."
        next
    end

    #some vars to hold value
    original = word
    total = 0
    score = 0
    #if the user puts a '2' or '3' at 
    #the beginning of the word, the word is scored as a double or triple word score. 
    #check if 1st letter is 2 or 3  
    totalMul = 1
    if word[0] == '2' || word[0] == '3'
        #if it is then set totalMul to the number
        totalMul = word[0].to_i
    else 
        #check to see if it is letter or digit
        #if digit then error message and then next
        if word[0].to_i != 0
            puts "Invalid multiplier '#{word[0]}'."
            next
        end
        #if not then set totalMul to 1
        totalMul = 1
        total += scores[word[0].upcase]
    end
  
    #If the user puts a 
    #'2' or '3' behind a letter, that letter is scored as a double or triple letter score.
    #loop through the input string and except the first letter
    #check to see if there is any 2 or 3 behind a letter  
    #if there is then multiply the score of the letter before number by the number
    #save the score of the letter before the number
    #if there is not then just add the score to total

    #flag for error case for output
    errFlag = false
    
    #loop through the input string and except the first letter
    for i in 1..word.length-1
        if word[i] == '2' || word[i] == '3'
            #if the letter before the number is not a letter then error
            if word[i-1].to_i != 0
                errFlag = true
                next
            end
            total += scores[word[i-1].upcase].to_i * word[i].to_i
            score += scores[word[i-1].upcase];
            errFlag = false
        else
            if word[i].to_i != 0
                puts "Invalid multiplier '#{word[i]}'."
                errFlag = true
                next
            end
            total += scores[word[i].upcase]
        end
    end

    #before output, multiply the total by the totalMul
    if errFlag == false
    total -= score   
    total *= totalMul
    #print the total score
    puts "Score for '#{original}' is: #{total}"
    end
end

puts "\n\nBye!\n\n"
