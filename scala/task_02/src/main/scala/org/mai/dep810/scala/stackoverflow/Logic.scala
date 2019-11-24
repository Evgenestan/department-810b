package org.mai.dep810.scala.stackoverflow

object Logic {

  //obtain all commetns from entities
  def getComments(entities: Seq[Entity]): Seq[Comment] =
  {
    entities
      .filter
      {
        case c : Comment => true
        case _ => false
      }
      .map
      {
        case entity@(comment: Comment) => entity
      }
  }

  //split entities by type
  def splitEntities(entities: Seq[Entity]): (Seq[User], Seq[Post], Seq[Comment], Seq[Vote], Seq[Badge], Seq[Tag]) = {
    (
      entities filter {case u : User => true case _ => false} map {case entity@(user: User) => entity},
      entities filter {case p : Post => true case _ => false} map {case entity@(post: Post) => entity},
      entities filter {case c : Comment => true case _ => false} map {case entity@(comment: Comment) => entity},
      entities filter {case v : Vote => true case _ => false} map {case entity@(vote: Vote) => entity},
      entities filter {case b : Badge => true case _ => false} map {case entity@(badge: Badge) => entity},
      entities filter {case t : Tag => true case _ => false} map {case entity@(tag: Tag) => entity}
    )
  }

  //populate fields owner, lastEditor, tags with particular users from Seq[Post] and tags from Seq[Tag]
  def enreachPosts(posts: Seq[Post], users: Seq[User], tags: Seq[Tag]): Seq[EnreachedPost] =
  {
    posts map (post =>EnreachedPost(
      post,
      users.find(user => user.id == post.ownerUserId).getOrElse(null),
      users.find(user => user.id == post.lastEditorUserId).getOrElse(null),
      tags.filter(tag => tag.wikiPostId == post.id)
    ))
  }
  //populate fields post and owner with particular post from Seq[Post] and user from Seq[User]
  def enreachComments(comments: Seq[Comment],posts: Seq[Post], users: Seq[User]): Seq[EnreachedComment] = {
    comments map (comment => EnreachedComment(
      comment,
      posts.find(post => post.id == comment.postId).getOrElse(null),
      users.find(user => user.id == comment.userId).getOrElse(null)
    ))
  }

  //find all links (like http://example.com/examplePage) in aboutMe field
  def findAllUserLinks(users: Seq[User]): Seq[(User, Seq[String])] = {
    val emailChecker = ".*\\s(\\w+@\\w+\\.\\w+).*"
    users map (user => (user,(user.about.split(" ") filter (str => str matches(emailChecker))).toSeq))
  }

  //find all users with the reputation bigger then reputationLImit with particular badge
  def findTopUsersByBadge(users: Seq[User], badges: Seq[Badge], badgeName: String, reputationLimit: Int): Seq[User] = {
    users.filter(user => user.id == (badges.find(badge => badge.name == badgeName).getOrElse(null)).userId && user.reputation > reputationLimit)
  }

}

case class EnreachedPost(
                        post: Post,
                        owner: User,
                        lastEditor: User,
                        tags: Seq[Tag]
                        )

case class EnreachedComment(
                          comment: Comment,
                          post: Post,
                          owner: User
                        )
