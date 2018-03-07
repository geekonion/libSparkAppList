@interface SparkAppListTableViewController : UITableViewController
@property (nonatomic, retain) NSArray* appList;

@property (nonatomic, retain) NSString* preferencesIdentifier;
@property (nonatomic, retain) NSString* preferencesKey;
@property (nonatomic, retain) NSMutableArray* preferencesAppList;

-(id)initWithIdentifier:(NSString*)identifier andKey:(NSString*)key;
@end