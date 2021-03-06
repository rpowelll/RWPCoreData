//
//  RWPRemoteManagedObject.h
//
//	The MIT License (MIT)
//
//	Copyright (c) 2014 Rhys Powell
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//	THE SOFTWARE.
//

/**
 `RWPRemoteManagedObject` subclasses `RWPManagedObject` to add some extra support
 for objects that are retrieved from a remote store such as a web service. It allows
 objects to be retrieved with a dictionary representation or remote ID as well
 as providing methods for unpacking dictionaries retrieved from a remote source.

 ## Subclassing Notes

 It is up to subclasses to implement their own implementations of `unpackDictionary:`
 and `shouldUnpackDictionary:`. The purpose of these methods is to map the data retrieved
 from the remote store to the class's own representation.

 Subclasses should also let their superclass be responsible for the `createdAt`,
 and `updatedAt` properties by not redefining them and calling the superclass's
 implementation of `unpackDictionary` before doing any of its own unpacking.
 
 Finally, each model must have a primary key. By default this will be the `remoteID`
 property, but if you want to use another name just override `remoteIDKeyPath`. You'll
 be responsible for setting this property's value.
 */

#import "RWPManagedObject.h"

@interface RWPRemoteManagedObject : RWPManagedObject

/** The date this object was created at */
@property (nonatomic, strong) NSDate *createdAt;

/** The date this object was last updated */
@property (nonatomic, strong) NSDate *updatedAt;

/** @name Instantiate an Object with a Remote ID */

+ (NSString *)remoteIDKeyPath;

/** Get or create an object for a given remote ID

 This method first tries to find an object with the given remote ID, if it can't
 find an object it will instead instantiate a new one and return that instead.

 @param remoteID the remote ID of the desired object

 @return an object of this class with the given remote ID
 */
+ (instancetype)objectWithRemoteID:(id)remoteID;

/** Get or create an object for a given remote ID

 This method first tries to find an object with the given remote ID, if it can't
 find an object it will instead instantiate a new one and return that instead.

 @param remoteID the remote ID of the desired object
 @param context the context to use, if set to nil the main context is used

 @return an object of this class with the given remote ID
 */
+ (instancetype)objectWithRemoteID:(id)remoteID context:(NSManagedObjectContext *)context;

/** Get an object for a given remote ID

 This method first tries to find an object with the given remote ID, if it can't
 find an object it will instead return `nil`.

 @param remoteID the remote ID of the desired object

 @return an object of this class with the given remote ID
 */
+ (instancetype)existingObjectWithRemoteID:(id)remoteID;

/** Get an object for a given remote ID

 This method first tries to find an object with the given remote ID, if it can't
 find an object it will instead return `nil`.

 @param remoteID the remote ID of the desired object
 @param context the context to use, if set to nil the main context is used

 @return an existing object of this class with the given remote ID
 */
+ (instancetype)existingObjectWithRemoteID:(id)remoteID context:(NSManagedObjectContext *)context;

/** @name Instantiate an Object with a Dictionary */

/** Instantiate an object from a dictionary representation

 This method first looks for an object with the ID contained in the passed
 dictionary. If the object is found and older than the passed in dictionary,
 it will be updated and returned, otherwise the current record will be returned.
 If the object is not found, a new one will be instantiated from the passed
 dictionary.

 @param dictionary the `NSDictionary` returned by the remote service

 @return an object of this class unpackd from `dictionary`
 */
+ (instancetype)objectWithDictionary:(NSDictionary *)dictionary;

/** Instantiate an object from a dictionary representation

 This method first looks for an object with the ID contained in the passed
 dictionary. If the object is found and older than the passed in dictionary,
 it will be updated and returned, otherwise the current record will be returned.
 If the object is not found, a new one will be instantiated from the passed
 dictionary.

 @param dictionary the `NSDictionary` returned by the remote service
 @param context the context to use, if set to nil the main context is used

 @return an object of this class unpackd from `dictionary`
 */
+ (instancetype)objectWithDictionary:(NSDictionary *)dictionary context:(NSManagedObjectContext *)context;

/** Find an object given dictionary representation

 This method will find an object that corresponds to the passed dictionary,
 if an object is not found it wil return `nil`.

 @param dictionary the `NSDictionary` returned by the remote service

 @return an object of this class unpackd from `dictionary`
 */
+ (instancetype)existingObjectWithDictionary:(NSDictionary *)dictionary;

/** Find an object given dictionary representation

 This method will find an object that corresponds to the passed dictionary,
 if an object is not found it wil return `nil`.

 @param dictionary the `NSDictionary` returned by the remote service
 @param context the context to use, if set to nil the main context is used

 @return an existing object of this class unpackd from `dictionary`
 */
+ (instancetype)existingObjectWithDictionary:(NSDictionary *)dictionary context:(NSManagedObjectContext *)context;

/** @name Override Methods */

/** Updates an object's properties with the contents of a dictionary

 @param dictionary the `NSDictionary` to be unpacked
 */
- (void)unpackDictionary:(NSDictionary *)dictionary;

/** Determines if an object needs to be updated with a given dictionary

 @param dictionary the `NSDictionary` to be compared to

 @return a `BOOL` indicating if the object should be unpacked
 */
- (BOOL)shouldUnpackDictionary:(NSDictionary *)dictionary;

/** @name Utilities */

/** Parses an ISO 8601 formatted date

 @param dateStringOrDateNumber an ISO 8601 encoded date string

 @return the `NSDate representation of the passed string
 */
+ (NSDate *)parseDate:(id)dateStringOrDateNumber;

@end
