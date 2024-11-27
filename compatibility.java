/* 
File: compatibility.java
Developer: ColorProgrammy

Description:
Code for checking the project's compatibility with the framework.
*/

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class VersionChecker {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Map<String, String> versionStatus = new HashMap<>();

        // List of versions
        versionStatus.put("1.0.0a", "Latest");
        
        System.out.print("DolphinEngine.\nCompatibility.\n\n")
        System.out.print("Enter the project version: ");
        String currentVersion = scanner.nextLine();
        
        if (!versionStatus.containsKey(currentVersion)) {
            System.out.println("\033[31mThis version does not exist, please check the project version for correctness.\033[0m");
            return;
        }
        
        String status = versionStatus.get(currentVersion);
        
        if ("Latest".equals(status)) {
            System.out.println("\033[32mThe project version matches yours, you can use it.\033[0m");
        } else if ("Outdated".equals(status)) {
            System.out.println("\033[31mThis version of the project is outdated (" + currentVersion + "). You will not be able to use it correctly.\033[0m");
        } else {
            System.out.println("\033[33mThe project version is lower than yours, but you can use it.\033[0m");
        }
        
        scanner.close();
    }
}
