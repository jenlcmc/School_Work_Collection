#Description: This function is to calculate the average score for each student
#and for each assignment then output it into html file 
#using functions and global variables

#global var
$posScoreHw = 0
$posScoreTest = 0
$total = 0
$totalHw = 0
$totalTest = 0
$testWeight = 0
$hwWeight = 0

#global array
$input = Array.new
$possArray = Array.new
$rowAve = Array.new
$colZero = Array.new
$colAve = Array.new

#make global string
$header = ""
$headerScore = ""
$posHeader = " "

#function to check if it is -ids or -names
#and if -ids then return id and if -names then return name
def checkIdName(input_array)
    if input_array[0] == "-ids" || input_array[0] == "-names"
        return input_array[0]
    else
        return "error"
    end
end

#check for input file is in the same directory or if it can find the file or not
def checkFile(input_array)
    if input_array[1] == nil
        return "error"
    elsif File.file?(input_array[1]) == false
        return "error"
    else
        return "ok"
    end
end

#function to read in the input file and parsing it with comma by using global array $input
def readFile(input_array)
    File.open(input_array[1]).each_with_index do |line, index|
        $input << line.split(",")
    end
end

#function to filter data
def filterData(input_array)
    #count how many student by running from row 8 to the end
    studentCount = $input[7..-1].length

    #get header from input file which is the first row
    $header = $input[0]
    #parse the header string and keep only 2nd column data
    $header = $header[1]

    #remove 1st row from $input
    $input.delete_at(0)

    #get total hw and remove that row from $input
    $total = $input[0][2].to_i + $input[1][2].to_i
    $totalHw = $input[0][2].to_i
    $totalTest = $input[1][2].to_i
    $input.delete_at(0)
    $input.delete_at(0)


    #get test weight & remove that row from $input
    $testWeight = $input[1][2].to_i / 100.0
    $hwWeight = $input[0][2].to_i / 100.0
    $input.delete_at(0)
    $input.delete_at(0)

    #get header score from input file which is the 1st row
    $headerScore = $input[0]
    #remove 1st row from $input
    $input.delete_at(0)

    #get possible scores of hw and test from $input
    #get 1st row from $input from column 2 to the end
    $posHeader = $input[0]
    $possArray = $input[0][2..-1]

    #call function to get possible scores of hw and test
    getPossScore($possArray)
    #remove 1st row from $input
    $input.delete_at(0)
end

#function to get possible scores of hw and test
def getPossScore(input_array)
    for i in 0..input_array.length-1
        #run from 1st column to totalHw column
        if i < $totalHw
            $posScoreHw += input_array[i].to_i
        else
            $posScoreTest += input_array[i].to_i
        end
    end
end

#function to clean up the $input array
def cleanUpInput(input_array)
    #sorting the array based on the 1st column number (ID)
    $input.sort! {|a,b| a[0].to_i <=> b[0].to_i}

    #then merge the column 2 and 3 (first name and last name) into 1 column
    for i in 0..$input.length-1
        $input[i][1] = $input[i][1] + " " + $input[i][2]
        #remobve the " " in that row
        $input[i][1].gsub!(/"/, "")
        $input[i].delete_at(2)
    end
end

#function to calculate the average score for each student 
#using formula (total score of hw / number of hw * (possible score of hw / 100)) 
# + (total score of exam / number of exam * (possible score of exam / 100)) 
def calcScore(input_array)
    #loop through input_array and calculate the the sum of hw and test for each student or each row 
    #if the cell is empty then add 0 
    #if the cell is not empty then add the score
    scoreHw = 0
    scoreTest = 0
    for i in 0..input_array.length-1
        for j in 2..input_array[i].length-1
            if input_array[i][j] == ""
                if j < $totalHw + 2
                    scoreHw += 0
                else
                    scoreTest += 0
                end
            else
                if j < $totalHw + 2
                    scoreHw += input_array[i][j].to_i
                else
                    scoreTest += input_array[i][j].to_i
                end
            end
        end
        #calculate the average score for each student
        #and add the average score to the $rowAve array
        tmp = (((scoreHw.to_f / $posScoreHw.to_f) * $hwWeight.to_f) + ((scoreTest / $posScoreTest.to_f) * $testWeight.to_f)) * 100
        tmp = tmp.round(2)
        $rowAve << tmp
        #reset the scoreHw and scoreTest to 0
        scoreHw = 0
        scoreTest = 0
    end
end

#function to calculate the column of average score of each assignment 
#using formula sum of colum / (total stundent - one that has 0)
def calcCol(input_array)

    #loop through input_array and calculate the the sum of each column
    #if the cell is empty then add 0
    #if the cell is not empty then add the score
    #then put the sum of each column into $colAve array
    for i in 2..input_array[0].length-1
        sum = 0
        for j in 0..input_array.length-1
            if input_array[j][i] == ""
                sum += 0
            else
                sum += input_array[j][i].to_i
            end
        end
        $colAve << sum
    end

    #add 2 0 to the front of $colAve array to act as null for ids and name
    $colAve.unshift(0)
    $colAve.unshift(0)


    #loop through the array from column 2 to the last column
    #convert the element to integer and replace those empty or nill or empty string with 0
    for i in 2..input_array[0].length-1
        for j in 0..input_array.length-1
            if input_array[j][i] == "" || input_array[j][i] == nil || input_array[j][i] == " "
                input_array[j][i] = 0
            else
                input_array[j][i] = input_array[j][i].to_i
            end
        end
    end
    
    sum = 0

    #calculate the total number of 0 in each column from column 2 to one last one and put it in $colZero array
    for i in 2..input_array[0].length-1
        for j in 0..input_array.length-1
            if input_array[j][i] == 0
                sum += 1
            end
        end
        $colZero << sum
        sum = 0
    end
    
    #add 2 0 to the front of $colAve array to act as null for ids and name
    $colZero.unshift(0)
    $colZero.unshift(0)

    tmp = 0

    #calculate the average score of each assignment
    #by using formula (sum of each column / (total student - number of 0 in that column))
    #run from 2nd column to the last column of $colAve array
    #no undefined method `-' for nil:NilClass problem need to avoid this by using if statement
    for i in 2..$colAve.length-1
        if $colZero[i] == $input.length
            tmp = 0
        else
            tmp = $colAve[i].to_f / ($input.length - $colZero[i]).to_f
        end
        tmp = tmp.round(1)
        $colAve[i] = tmp
    end
end

#function to output into html file
def outputHtml(fileName)
    #create a new file with the name of the input file
    #and add .html to the end of the file name
    #if the file already exist then delete it
    if File.exist?(fileName + ".html")
        File.delete(fileName + ".html")
    end
    #create a new file with the name of the input file
    #and add .html to the end of the file name
    file = File.new(fileName + ".html", "w+")

    #write the header of the html file
    file.puts "<!DOCTYPE html>"
    file.puts "<html>"
    file.puts "<head>"
    file.puts "<title>#{fileName}</title>"
    file.puts "</head>"

    file.puts "<body>"
    #output the $header first 
    file.puts "<h1>#{$header}</h1>"
    #output today date in the format of "Wed, Month, Day, Year"
    file.puts "<h2>As of: #{Time.now.strftime("%a, %b %d, %Y")}</h2>"
    file.puts "<table border='2'>"
    file.puts "<tr>"
    #output the header of the table which is $headerScore
    #for $headerScore, add extra column which is name "Ave" into last column
    #if fileName is names then output all column and add extra "Ave" in last colum
    #if fileNam is scores then skip the name which is column 2
    if fileName == "names"
        for i in 0..$headerScore.length-1
            file.puts "<th>#{$headerScore[i]}</th>"
        end
        file.puts "<th>Ave</th>"
    else
        for i in 0..$headerScore.length-1
            if i != 1
                file.puts "<th>#{$headerScore[i]}</th>"
            end
        end
        file.puts "<th>Ave</th>"
    end
    file.puts "</tr>"
    
    #output the content of the table which is $input
    #for the last column, "Ave", use the $rowAve array for student average
    #if fileName is names then output all column and add extra "Ave" in last colum
    #if fileNam is scores then skip the name which is column 2
    #for any cell that has 0, output " " instead of 0
    if fileName == "names"
        for i in 0..$input.length-1
            file.puts "<tr>"
            for j in 0..$input[i].length-1
                if $input[i][j] == 0
                    file.puts "<td> </td>"
                else
                    file.puts "<td>#{$input[i][j]}</td>"
                end
            end
            file.puts "<td>#{$rowAve[i]}</td>"
            file.puts "</tr>"
        end
    else
        for i in 0..$input.length-1
            file.puts "<tr>"
            for j in 0..$input[i].length-1
                if j != 1
                    if $input[i][j] == 0
                        file.puts "<td> </td>"
                    else
                        file.puts "<td>#{$input[i][j]}</td>"
                    end
                end
            end
            file.puts "<td>#{$rowAve[i]}</td>"
            file.puts "</tr>"
        end
    end

    #output the last row of the table which is the average score of each assignment
    #replace 1st column with "Ave"
    #skip the 2nd column which is name
    #but if fileName is names then have to keep 2nd column but replace it with " "
    #and output the rest of the column from column 3 to the last column
    file.puts "<tr>"
    file.puts "<td>Average</td>"
    if fileName == "names"
        file.puts "<td> </td>"
        for i in 2..$colAve.length-1
            file.puts "<td>#{$colAve[i]}</td>"
        end
    else
        for i in 2..$colAve.length-1
            file.puts "<td>#{$colAve[i]}</td>"
        end
    end
    file.puts "</tr>"

    


    #add last row into the table which is output the $posHeader
    #skip the 1st column of $posHeader which is empty
    #and output the rest of the column
    #if the fileName is names replace 1st column with "Possible"
    #and second column wth " "
    #and start to output from column 3 to the last column
    
    file.puts "<tr>"
    if fileName == "names"
        file.puts "<td>Possible</td>"
        file.puts "<td> </td>"
        for i in 2..$posHeader.length-1
            file.puts "<td>#{$posHeader[i]}</td>"
        end
    else
        for i in 1..$posHeader.length-1
            file.puts "<td>#{$posHeader[i]}</td>"
        end
    end
    file.puts "</tr>"
    file.puts "</table>"

    #skip few space lines and output the grading formula
    file.puts "<br>"
    file.puts "<br>"
    file.puts "<br>"

    file.puts "<h3>Grading Formula:</h3>"
    # [((homework scores/possible) * $hwWeight) + ((test scores/possible) * $testWeight)
    file.puts "<p>[(homework scores/possible) * #{$hwWeight}] + [(test scores/possible) * #{$testWeight})]</p>"
    file.puts "</body>"
    file.puts "</html>"

    #close the file
    file.close
end

#This is main function
#which is call other functions
#read command line for input file name and output html file
input_array = ARGV
if(checkIdName(input_array) == "error")
    puts "error. Not -ids or -names"
    exit
end

#check for input file is in the same directory or if it can find the file or not
if(checkFile(input_array) == "error")
    puts "error. File not found"
    exit
end

#read file and store the content into $input array
readFile(input_array)

#filter the data and put it into global vars for easier access
filterData($input)

#clean up the data for better format and easier $input
cleanUpInput($input)

#calculate the average score for each students
calcScore($input)

#calculate the average score for each assignment
calcCol($input)

#make an html file depending on the command line -ids or -names
if input_array[0] == "-ids"
    outputHtml("scores")
elsif input_array[0] == "-names"
    outputHtml("names")
end