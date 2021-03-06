//
//  RWPManagedObject.h
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

#import <CoreData/CoreData.h>

#import "NSDictionary+RWPExtensions.h"

/**
 A subclass of `NSManagedObject` that makes Core Data model
 code much cleaner and easier to maintain.
 */
@interface RWPManagedObject : NSManagedObject

/** @name Accessing the Main Context */

/**
 Get the shared main context used by objects in this app
 
 @return a main context
 */
+ (NSManagedObjectContext *)mainContext;

/** 
 Whether or not a main context has been created yet
 
 @return whether or not the main context exists yet
 */
+ (BOOL)hasMainContext;

/** @name Configuring the Persistent Store */

/** 
 Get the shared persistent store coordinator
 
 @return the shared persistent store coordinator
 */
+ (NSPersistentStoreCoordinator *)persistentStoreCoordinator;

/**
 Get the default persistent store options
 
 @return the default persistent store options
 */
+ (NSDictionary *)persistentStoreOptions;

/**
 Set the default persistent store options, these will be used
 when the app creates a persistent store for the first time.
 This means these options should be set early in the application's
 lifecycle, Ideally in your app delegate's implementation of
 `application:didFinishLaunchingWithOptions:`
 
 @param options the options to use when creating a persistent store
 */
+ (void)setPersistentStoreOptions:(NSDictionary *)options;

/** 
 The app's managed object model. If none has been set yet, this
 will default to merging and loading all the data models in the
 app bundle.
 
 @return the app's managed object model
 */
+ (NSManagedObjectModel *)managedObjectModel;

/**
 Set the app's managed object model. You'll rarely need to do
 this manually, unless your app has more than one data model.
 
 @param model the model to use
 */
+ (void)setManagedObjectModel:(NSManagedObjectModel *)model;

/**
 Get the app's persistent store URL
 
 @return a persistent store URL
 */
+ (NSURL *)persistentStoreURL;

/**
 Set the persistent store's URL. Most of the time you can just
 leave this alone and use the default URL.
 
 @param url the URL to use for our persistent store
 */
+ (void)setPersistentStoreURL:(NSURL *)url;

/** @name Getting Entity Information */

/** 
 The name of the entity mapped to this model. You **must**
 override this in your subclass.
 
 @return the name of the entity mapped to this model
 */
+ (NSString *)entityName;

/**
 The entity description for this model, based on `entityName`
 and in the default context.
 
 @return the entity description for this model
 */
+ (NSEntityDescription *)entity;

/**
 The entity description for this model, based on `entityName`
 and in a custom context.

 @param context the managed object context to use

 @return the entity description for this model
 */
+ (NSEntityDescription *)entityWithContext:(NSManagedObjectContext *)context;

/**
 To be overridden by subclasses of `RWPManagedObject`, this 
 sets a default order for models of the subclass's type.
 
 @return an array of `NSSortDescriptor` objects
 */
+ (NSArray *)defaultSortDescriptors;

/** @name Initializing */

/** 
 Initialize a new object of this model in the provided context.
 If the provided context is `nil`, the main context will be used
 instead.
 
 @param context the context to initialize this object in
 
 @return a new model object
 */
- (instancetype)initWithContext:(NSManagedObjectContext *)context;

/** @name Persistence */

/**
 Save's a model's managed object context
 
 *Note:* Doing this will save any other objects that share
 a managed object context with this object
 */
- (void)save;

@end
