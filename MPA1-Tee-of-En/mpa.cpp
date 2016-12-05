import java.util.*;
import java.io.*;
import java.lang.*;

public class mp {

    // this function operates every for Loop given from the file
    public static void operatePerLoop(String[] stringArr){
        int i = 1;
        while (i < stringArr.length){
            List<String> arrList2 = new ArrayList<String>();
            for ( ;i < stringArr.length; i++){
                if (!(stringArr[i].equals("for")))    
                    arrList2.add(stringArr[i]);
                else break;
                } i++;
                String[] array = arrList2.toArray(new String[0]);  
                    teeOfEn(array);
        }
    } 
    // this function counts the operations given a string
    public static int operationsCount(String arr) {
        String arr2 = arr.replaceAll("\\s+","");
        char[] charArr = new char[arr2.length()];
        for (int i = 0; i < charArr.length; i++) {
            charArr[i] = arr2.charAt(i);
        }
        char[] operations = {'+', '-', '*', '/', '=', '!', '>', '<'};
        int count = 0;
        for (int i = 1; i < arr2.length(); i++){
            for (int j = 0; j < operations.length; j++){
                if (charArr[i] == operations[j] && charArr[i - 1] != ' '){
                    charArr[i] = ' '; count++; 
                }
            }
        } return count;
    } 
    // this function counts the operations from condition to end of for loop
    public static int count(String[] arr){
        int count = 0;
        for (int i = 1; i < arr.length; i++){
            count += operationsCount(arr[i]);
        } return count;
    } 
    // this function returns the lower bound of the loop
    public static String lowerBound(String[] array){
        List<String> arrList = new ArrayList<String>();
        StringTokenizer strTok = new StringTokenizer(array[0],",");
        String token = "";
            while (strTok.hasMoreTokens()){
                token = strTok.nextToken().trim();
                    arrList.add(token);
                }   
        String[] arr = arrList.toArray(new String[0]);
        String condition = array[1].replaceAll("\\s+","");
        char conditionVar = condition.charAt(0);
        String ans = "";
        int index = 0;
        for (int i = 0; i < arr.length; i++){
            if (arr[i].charAt(4) == conditionVar) {
                index = i; break; 
            }
        }
        for (int j = 1; j < arr[index].length(); j++){
            if (arr[index].charAt(arr[index].length() - 1) >= '0' && arr[index].charAt(arr[index].length() - 1) <= '9') {
                    ans = Integer.parseInt(arr[index].replaceAll( "[^\\d]", "")) + ""; break;
            } else {
                    ans = arr[index].charAt(arr[index].length() - 1) + ""; break;
                }
            }
        return ans;
    } 
    // this function returns the upper bound of the loop
    public static String upperBound(String[] arr){
        String end = arr[1].replaceAll("\\s+","");
        String ans = Character.isLetter(end.charAt(end.length() - 1)) ? end.charAt(end.length() - 1) + "": 
        Integer.parseInt(end.replaceAll( "[^\\d]", "")) + "";
        return ans;
    } 
    // this function checks if the loop is infinite or only has T(n) of 2
    public static boolean checkForErrors(String[] arr){
        String upper = upperBound(arr), lower = lowerBound(arr);
        String increment = arr[2].replaceAll("\\s+","");
        boolean check = false;
        if (increment.equals("i--") && lower.equals("1")) {
            System.out.println("T(n) = infinite"); check = true;
        } else if (increment.equals("i--") && lower.equals("n")){
            System.out.printf("T(n) = %d", operationsCount(arr[0]) + 1); check = true;
        } else if (operationOfCondition(arr[1]).equals(">")){
            System.out.printf("T(n) = %d", operationsCount(arr[0]) + 1); check = true;
        } else if (arr[2].charAt(2) == '/'){
            System.out.printf("T(n) = %d", operationsCount(arr[0]) + 1); check = true;
        } return check;
    } 
    // this function returns the Greatest Common Factor given two ints
    public static int findGCD(int num1, int num2) {
        if(num2 == 0){
            return num1;
        } return findGCD(num2, num1 % num2);
    } 
    // this function returns the operation/s of the condition
    public static String operationOfCondition(String condition){
        char[] operations = {'+', '-', '*', '/', '=', '!', '>', '<'};
        List<Character> conditionOperation = new ArrayList<Character>();
        for (int i = 0; i < condition.length(); i++){
            for (int j = 0; j < operations.length; j++){
            if (condition.charAt(i) == operations[j])
                conditionOperation.add(condition.charAt(i));
            }
        } String conditionOp = new String();
              for (char c: conditionOperation)
                 conditionOp += c;
              return conditionOp;
    } 
    // this function checks if the upper bound is N or N - 1
    public static boolean upperCheck(String[] arr){
        for (int i = 0; i < arr[1].length(); i++){
            if (arr[1].charAt(i) == '=')
               return true;
        } return false;
    }
    // this function returns the increment operation of the loop
    public static String increment(String[] array){
        List<String> arrList = new ArrayList<String>();
        StringTokenizer strTok = new StringTokenizer(array[2],",");
        String token = "";
            while (strTok.hasMoreTokens()){
                token = strTok.nextToken().trim();
                    arrList.add(token);
            }   
        String[] arr = arrList.toArray(new String[0]);
        String condition = array[1].replaceAll("\\s+","");
        char conditionVar = condition.charAt(0);
        for (int i = 0; i < arr.length; i++){
            if (arr[i].charAt(0) == conditionVar)
                return arr[i];
        } return "";
    }
    // this function prints the Time Complexity of a for loop
    public static void teeOfEn(String[] arr){
        int lastCount = operationsCount(arr[0]) + 1, countAsterisk = 0, count = count(arr);
        String ans = "", temp = "";
        String condition = arr[1], increment = increment(arr);
        String up = upperBound(arr), lower = lowerBound(arr);
        String var = Character.isLetter(upperBound(arr).charAt(up.length()-1)) ? up : lower;
        boolean upperCheck = false, log = false, decrement = false;
        boolean fractionPlus = false, fractionMinus = false;
        int logBase = increment.equals("i++") || increment.equals("i--") ? 0 : 
        Integer.parseInt(increment.replaceAll( "[^\\d]", ""));
        // checking if the T(n) of the loop is 2 or infinite
        if (checkForErrors(arr) == true){
        } else {
        for (int i = 0; i < increment.length(); i++){
            if (increment.charAt(i) == '*'){
                log = true; break;
            } else if (!(increment.equals("i++") || increment.equals("i--"))) {
                if (increment.charAt(i) == '+'){
                    fractionPlus = true; break;
                } else if (increment.charAt(i) == '-'){
                    fractionMinus = true; 
                    up = lowerBound(arr); 
                    lower = upperBound(arr);
                }
            } else if (increment.equals("i--")){
                decrement = true; 
                lower = upperBound(arr); 
                up = lowerBound(arr); break;
            }
        }

        for (int i = 0; i < condition.length(); i++){
            if (condition.charAt(i) == '*')
                countAsterisk++;
        }
        if (log) {
            if (upperCheck(arr)){
                if (Character.isLetter(up.charAt(0))){
                    temp = ((((-1 * Integer.parseInt(lower)) + 1) * count) + lastCount) + "";
                    if (temp.charAt(0) == '-')
                        System.out.printf("T(n) = %d log(%s) %s - %d\n", count, logBase, var, Integer.parseInt(temp) * -1);
                    else System.out.printf("T(n) = %d log(%s) %s + %s\n", count, logBase, var, temp);
                } else System.out.printf("T(n) = %d + %d", count*(Integer.parseInt(up) - Integer.parseInt(lower) + 1), lastCount);
            } else {
                if (Character.isLetter(up.charAt(0))){
                    temp = (((-1 * Integer.parseInt(lower)) * count) + lastCount) + "";
                    if (temp.charAt(0) == '-')
                        System.out.printf("T(n) = %d log(%s) %s - %d\n", count, logBase, var, Integer.parseInt(temp) * -1);
                    else System.out.printf("T(n) = %d%s + %s\n", count,var, temp);
                } else System.out.printf("T(n) = %d\n", count * (Integer.parseInt(up) - Integer.parseInt(lower)) + lastCount);
            }
        } else if (fractionPlus || fractionMinus) {
            int incre = Integer.parseInt(increment.replaceAll( "[^\\d]", ""));
            int gcd = findGCD(count, incre);
            if (upperCheck(arr)){
                if (Character.isLetter(up.charAt(0))){
                    temp = ((((-1 * Integer.parseInt(lower)) + 1) * count) + lastCount) + "";
                    if (incre/gcd == 1){
                        if (temp.charAt(0) == '-')
                            System.out.printf("T(n) = %d%s - %d\n", count/gcd,var, Integer.parseInt(temp) * -1);
                        else System.out.printf("T(n) = %d%s + %s\n", count/gcd, var, temp);
                    } else {
                        if (temp.charAt(0) == '-')
                            System.out.printf("T(n) = %d%s/%d - %d\n", count/gcd, var, incre/gcd, Integer.parseInt(temp) * -1);
                        else System.out.printf("T(n) = %d%s/%d + %s\n", count/gcd, var, incre/gcd, temp); 
                    }
                } else System.out.printf("T(n) = %d", count * (Integer.parseInt(up) - Integer.parseInt(lower) + 1) + lastCount);
            } else {
                if (Character.isLetter(up.charAt(0))){
                    temp = (((-1 * Integer.parseInt(lower)) * count) + lastCount) + "";
                    if (incre/gcd == 1){
                        if (temp.charAt(0) == '-')
                            System.out.printf("T(n) = %d%s - %d\n", count/gcd, var, Integer.parseInt(temp) * -1);
                        else System.out.printf("T(n) = %d%s + %s\n", count/gcd, var, temp);
                    } else {
                        if (temp.charAt(0) == '-')
                            System.out.printf("T(n) = %d%s/%d - %d\n", count/gcd,var, incre/gcd, Integer.parseInt(temp) * -1);
                        else System.out.printf("T(n) = %d%s/%d + %s\n", count/gcd, var, incre/gcd, temp);
                    }
                } else System.out.println((count * (Integer.parseInt(up) - Integer.parseInt(lower)) + lastCount) + "");
            }
        } else if (countAsterisk > 0) {
            String sqrtOrcubert = (countAsterisk == 1) ? "sqrt" : "cubert";
            int lastCount2 = sqrtOrcubert.equals("sqrt") ? lastCount + 1 : lastCount + 2;
            if (upperCheck(arr)){
                if (Character.isLetter(up.charAt(0))){
                    temp = ((((-1 * Integer.parseInt(lower)) + 1) * count) + lastCount2) + "";
                    if (temp.charAt(0) == '-')
                        System.out.printf("T(n) = %d %s(%s) - %d\n", count, sqrtOrcubert, var, Integer.parseInt(temp) * -1);
                    else System.out.printf("T(n) = %d %s(%s) + %s\n", count, sqrtOrcubert, var, temp);
                } else
                    System.out.printf("T(n) = %d", count * (Integer.parseInt(up) - Integer.parseInt(lower) + 1) + lastCount2);
            } else {
                if (Character.isLetter(up.charAt(0))){
                    temp = (((-1 * Integer.parseInt(lower)) * count) + lastCount2) + "";
                    if (temp.charAt(0) == '-')
                        System.out.printf("T(n) = %d %s(%s) - %d\n", count, sqrtOrcubert, var, Integer.parseInt(temp) * -1);
                    else System.out.printf("T(n) = %d%s + %s\n", count,var, temp);
                } else System.out.printf("T(n) = %d\n", count * (Integer.parseInt(up) - Integer.parseInt(lower)) + lastCount2);
            }
        } else if (decrement) {
            if (upperCheck(arr)){
                if (Character.isLetter(up.charAt(0))){
                    temp = ((((-1 * Integer.parseInt(lower)) + 1) * count) + lastCount) + "";
                    if (temp.charAt(0) == '-')
                        System.out.printf("T(n) = %d%s - %d\n", count, var,Integer.parseInt(temp) * -1);
                    else System.out.printf("T(n) = %d%s + %s\n", count,var, temp); 
                } else System.out.printf("T(n) = %d\n", count * (Integer.parseInt(up) - Integer.parseInt(lower) + 1) + lastCount);
            } else {
                if (Character.isLetter(up.charAt(0))){
                    temp = (((-1 * Integer.parseInt(lower)) * count) + lastCount) + "";
                    if (temp.charAt(0) == '-')
                        System.out.printf("T(n) = %d%s - %d\n", count, var,Integer.parseInt(temp) * -1);
                    else System.out.printf("T(n) = %d%s + %s\n", count, var, temp); 
                } else System.out.printf("T(n) = %d\n", count * (Integer.parseInt(up) - Integer.parseInt(lower)) + lastCount);
            }
        } else {
            if (upperCheck(arr)){
                if (Character.isLetter(up.charAt(0))){
                    temp = ((((-1 * Integer.parseInt(lower)) + 1) * count) + lastCount) + "";
                    if (temp.charAt(0) == '-')
                        System.out.printf("T(n) = %d%s - %d\n", count,var, Integer.parseInt(temp) * -1);
                    else System.out.printf("T(n) = %d%s + %s\n", count, var,temp);
                } else System.out.printf("T(n) = %d\n", (count * (Integer.parseInt(up) - Integer.parseInt(lower) + 1) + lastCount));
            } else {
                if (Character.isLetter(up.charAt(0))){
                    temp = (((-1 * Integer.parseInt(lower)) * count) + lastCount) + "";
                    if (temp.charAt(0) == '-')
                        System.out.printf("T(n) = %d%s - %d\n", count,var,Integer.parseInt(temp) * -1);
                    else System.out.printf("T(n) = %d%s + %s\n", count,var, temp); 
                } else System.out.printf("T(n) = %d\n", count * (Integer.parseInt(up) - Integer.parseInt(lower)) + lastCount);
            }
        }
    }
}
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(new File("sample-test-cases.txt"));
        String token = "", line = "";
        List<String> array = new ArrayList<String>();
            while (sc.hasNextLine()) {
                line = sc.nextLine();
                StringTokenizer strTok = new StringTokenizer(line,";()");
                while (strTok.hasMoreTokens()){
                    token = strTok.nextToken().trim();
                    array.add(token);
                }   
            }
            sc.close();
            String[] arr = array.toArray(new String[0]);
            operatePerLoop(arr);
    }
}
