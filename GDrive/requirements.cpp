/*

# Capacity Estimtion
    - 500M Total users, 100M DAU
    - 0.07M user/minute active ~ 1M active users/min
    - 1 User upload 5 files => 5M uploads/min
    - 1 Upload ~ 100 KB => 500 TB/min


# API
    - Upload file // first metadata then file uploaded
        POST: /file
        Request {
          filename: string,
          createdOnInUTC: long,
          createdBy: string,
          updatedOnInUTC: long,
          updatedBy: string
        }

        Response: {
          fileId: string,
          downloadUrl: string
        }

    - Download file
        GET: /file/{fileId}
        Response: {
          fileId: string,
          downloadUrl: string
        }

    - Delete file
        DELETE: /file/{fileId}

    - Get Latest Snapshot
        GET: /folders/{folderId}?startIndex={startIndex}&limit={limit}
        Response: {
          folderId: string,
          fileList: [ 
            {
              fileId: string,
              filename: string,
              thumbnail_img: string,
              lastModifiedDateInUTC: string
              creationDateInUTC: string
            }
          ]
        }


# DB Design
    - User Table
        userId: string
        username: string
        emailId: string
        creationDateInUtc: long

    - Metadata table
        fileId: string
        userId: string
        filename: string
        fileLocation: string
        creationDateInUtc: long
        updationDateInUtc: long














*/