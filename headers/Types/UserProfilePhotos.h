#ifndef USERPROFILEPHOTOS_H
#define USERPROFILEPHOTOS_H

#include "Types/Type.h"
#include "Types/PhotoSize.h"

class UserProfilePhotos : public Type
{
public:
    UserProfilePhotos();

    UserProfilePhotos(qint32                      totalCount,
                      QVector<QVector<PhotoSize>> photos);

    UserProfilePhotos(QJsonObject jsonObject);

    qint32 totalCount();
    void   setTotalCount(qint32 totalCount);

    QVector<QVector<PhotoSize>> photos();
    void                        setPhotos(QVector<QVector<PhotoSize>> photos);
};

#endif // USERPROFILEPHOTOS_H
