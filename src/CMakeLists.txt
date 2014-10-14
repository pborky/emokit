##########################################
##              libemokit              ###
##########################################

# Create a library called "libepoc"
ADD_LIBRARY (emokit SHARED emokit.c) 
target_link_libraries (emokit ${LIBS}) 

INSTALL (TARGETS emokit
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )

INSTALL(FILES
  emokit.h
  DESTINATION include/emokit
  )
