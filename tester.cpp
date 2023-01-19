
//    test.resize(5);
//
//    Vertex v1(coord(0,0), coord(0,1));
//    Vertex v2(coord(1,0), coord(1,1));
//    Vertex v3(coord(2,0), coord(2,1));
//    Vertex v4(supertriangle(2,0), supertriangle(2,1));
//
//    test[0] = &v1;
//    test[1] = &v2;
//    test[2] = &v3;
//    test[3] = &v1;
//    test[4] = &v2;
//    test[5] = &v4;

//    cout <<  endl;
//    cout << "test size: ";
//    cout << test.size() << ", ";
//
//    delete test[4];
//    cout << test.size() << ", ";
//    delete test[4];
//    cout << test.size() << ", ";


//    test.erase(test.begin()+1);
//    cout << test.size() << ", ";
//    test.erase(test.begin()+1);
//    cout << test.size() << endl;

//    for (int i = 0; i<test.size(); i++) {
//        for (int j = 0; j < test.size(); j++) {
//            if (i != j) {
//
//                cout << i << " and " << j << ": ";
//                cout << test[i] << " and " << test[j];
//
//                if (test[i] == test[j]) {
//                    cout << " same" << endl;
//                    break;
//                }
//            }
//            if (j == (test.size()-1)) {
//                test1.push_back(test[i]);
//            }
//            cout <<  endl;
//        }
//        cout <<  endl;
//    }