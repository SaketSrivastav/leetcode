int numUniqueEmails(vector<string>& emails) {
    // Hash set to store only unique items
    unordered_set<string> result = {};
    for(auto email : emails) {
        string uniq_email;
        for(int i=0; i<email.length(); i++) {
            if(email[i] == '.') continue;
            if(email[i] == '+') {
                while(email[i] != '@' && i < email.length()) {
                    i++;
                }

                if(i == email.length()) break;
                // copy from @ to end of string
                uniq_email.append(email.substr(i));
            }
            uniq_email.push_back(email[i]);
        }

        // store in hash set
        result.insert(uniq_email);
    }

    return result.size();
}
